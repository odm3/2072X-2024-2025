#include "main.h"
#include "pros/rtos.hpp"
#include "gif-pros/gifclass.hpp"
#include "display/lvgl.h"
#include "pros/apix.h"
#include "screen.hpp"
#include "autons.hpp"
#include <vector>
#include "api.h"
#include <cstdlib> 
#include <cmath>
#include <ctime> 
#include <fstream>
#include <stdio.h>

// Function to make a color lighter or darker
lv_color_t color_shade(lv_color_t base_color, int percentage) {
    // Separate the color into its RGB components
    int red = lv_color_to32(base_color) >> 16 & 0xFF;
    int green = lv_color_to32(base_color) >> 8 & 0xFF;
    int blue = lv_color_to32(base_color) & 0xFF;

    // Calculate the adjustment based on the percentage
    float adjust = (100 + percentage) / 100.0f;

    // Adjust and clamp each color component
    red = std::min(std::max(0, static_cast<int>(red * adjust)), 255);
    green = std::min(std::max(0, static_cast<int>(green * adjust)), 255);
    blue = std::min(std::max(0, static_cast<int>(blue * adjust)), 255);

    // Recombine the color components and cast to uint8_t to avoid narrowing conversion
    return LV_COLOR_MAKE(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
}


std::string pickRandomString(const std::string strings[], int size) {
    double voltage = pros::battery::get_voltage();
    double capacity = pros::battery::get_capacity();
    double current = pros::battery::get_current();
    double temperature = pros::battery::get_temperature();

    double seedValue = pow((voltage * capacity * current * temperature), 3.0);

    unsigned int seed = static_cast<unsigned int>(fmod(seedValue, UINT_MAX));

    // Seed the random number generator
    srand(seed);    
    
    // Check if the size is not zero to avoid division by zero
    if (size <= 0) {
        return ""; // Or handle the error as appropriate
    }

    // Generate a random index between 0 and size - 1
    int index = rand() % size;

    // Return the string at the random index
    return strings[index];
}

bool chassisCalibrated = false;

// these are the gifs that will display randomly for the calibration screen
std::string calibrationGifs[] = {
                "/usd/jq-griddy.gif", 
                "/usd/dog-angry.gif", 
                "/usd/carnage-venom.gif", 
                "/usd/beastboy.gif", 
            };

// these are the gifs that will display randomly during the match
std::string matchGifs[] = {
                "/usd/getreal.gif", 
            };

int matchGifsSize = sizeof(matchGifs) / sizeof(matchGifs[0]);
int calibrationGifsSize = sizeof(calibrationGifs) / sizeof(calibrationGifs[0]);

void calibrationScreen() {
    // Get a random gif string
    std::string randomGif = pickRandomString(calibrationGifs, calibrationGifsSize);

    // Create a new Gif object with the random string as a C-style string
    Gif* caliGif = new Gif(randomGif.c_str(), lv_scr_act());

    while (!chassisCalibrated) {
        pros::delay(25);
    }

    caliGif->clean(); 
}


void calibrationScreenInit() {
    pros::Task calibrationScreenTask(calibrationScreen); 
}

lv_obj_t *roller;
lv_obj_t *confirmBtn;
lv_obj_t *confirmLabel;
Gif *textGif;
int selectedAuton = 8;

int readSelectedAutonFromFile() {
    selectedAuton = 8;  // Default value
    FILE* usd_file_read = fopen("/usd/auton_selection.txt", "r");

    if (usd_file_read == NULL) {
        // File does not exist or cannot be opened, default to 0
        return selectedAuton;  // Return the default value
    }

    // If the file exists, read the integer value
    if (fscanf(usd_file_read, "%d", &selectedAuton) != 1) {
        // If reading fails or the data is not an integer, default to 0
        selectedAuton = 8;
    }

    fclose(usd_file_read);  // Always close the file
    return selectedAuton;  // Return the read or default value
}

void setSelectorOptions(lv_obj_t *roller, size_t autonCount, AutonFunction autonFunctions[]) {
    // Calculate the length needed for the options string
    size_t optionsLength = 0;
    for (size_t i = 0; i < autonCount; ++i) {
        optionsLength += strlen(autonFunctions[i].name) + 1; // +1 for the newline character
    }

    // Allocate memory for the options string
    char *options = (char *)malloc(optionsLength + 1); // +1 for the null terminator
    if (options == NULL) {
        // Handle memory allocation error
        return;
    }

    // Concatenate all auton names into the options string
    char *currentPosition = options;
    for (size_t i = 0; i < autonCount; ++i) {
        strcpy(currentPosition, autonFunctions[i].name);
        currentPosition += strlen(autonFunctions[i].name);
        *currentPosition = '\n'; // Add newline character
        currentPosition++;
    }
    *(currentPosition - 1) = '\0'; // Replace the last newline character with a null terminator

    // Set the roller options
    lv_roller_set_options(roller, options);

    // Free the memory for the options string
    free(options);
}

void autonList(lv_obj_t *scr, lv_color_t color_scheme, AutonFunction autonFunctions[], size_t autonCount) {
    // Create a style for the roller background
    static lv_style_t style_bg;
    lv_style_copy(&style_bg, &lv_style_plain);
    style_bg.body.main_color = LV_COLOR_BLACK; // Background color
    style_bg.body.grad_color = LV_COLOR_BLACK; // Background color
    style_bg.body.shadow.color = LV_COLOR_SILVER; // Shadow effect for cool look
    style_bg.body.shadow.width = 5; // Set the shadow width
    style_bg.body.radius = LV_DPI / 30; // Rounded corners for the background
    style_bg.body.padding.hor = LV_DPI / 12; // Horizontal padding
    style_bg.body.padding.ver = LV_DPI / 12; // Vertical padding
    style_bg.text.font = &lv_font_dejavu_20;
    style_bg.text.color = color_scheme; // text color
    style_bg.text.opa = LV_OPA_COVER; // Ensure full opacity for the text

    // Create a style for the roller's selected item
    static lv_style_t style_sel;
    lv_style_copy(&style_sel, &lv_style_plain);
    style_sel.body.main_color = LV_COLOR_BLACK; // Background color for selected item
    style_sel.body.grad_color = LV_COLOR_BLACK; // Background color for selected item
    style_sel.body.border.color = LV_COLOR_WHITE; // Border color for the selection
    style_sel.body.border.width = 2; // Set the border width
    style_sel.body.radius = LV_DPI / 30; // Rounded corners for the selection
    style_sel.text.color = color_scheme; // text color
    style_sel.text.opa = LV_OPA_COVER; // Ensure full opacity for the text
    
    // Create the roller
    roller = lv_roller_create(scr, NULL);
    setSelectorOptions(roller, autonCount, autonFunctions);

    // Apply the styles to the roller
    lv_roller_set_style(roller, LV_ROLLER_STYLE_BG, &style_bg); // Apply the background style
    lv_roller_set_style(roller, LV_ROLLER_STYLE_SEL, &style_sel); // Apply the style for the selected item

    // Calculate the width and height for the roller with padding
    int roller_width = lv_obj_get_width(scr) / 3 - (style_bg.body.padding.hor * 2);
    int roller_height = lv_obj_get_height(scr) - (style_bg.body.padding.ver * 2);

    // Set the size of the roller
    lv_obj_set_size(roller, roller_width, roller_height);

    // Align the roller with padding from the left side of the screen
    lv_obj_align(roller, NULL, LV_ALIGN_IN_LEFT_MID, style_bg.body.padding.hor, 0);
}

// Function to be called when the confirm button is pressed
static lv_res_t confirm_btn_action(lv_obj_t *btn) {    
    // Get the selected option index from the roller
    selectedAuton = lv_roller_get_selected(roller);
    FILE* usd_file_write = fopen("/usd/auton_selection.txt", "w");
    fprintf(usd_file_write, "%d\n", selectedAuton); 
    fclose(usd_file_write);
    

    // Create a new screen
    lv_obj_t *new_scr = lv_obj_create(NULL, NULL);


    // Load the new screen
    lv_scr_load(new_scr);

    // Ensure mainScreenGif is not null and is properly initialized

    return LV_RES_OK;
}

lv_obj_t confirmButton(lv_obj_t *scr, lv_color_t color_scheme) { 
    // Create a style for the confirm button
    static lv_style_t style_btn;
    lv_style_copy(&style_btn, &lv_style_btn_rel); // Copy a base button style to start with
    style_btn.body.main_color = color_scheme; // Use the passed color
    style_btn.body.grad_color = color_shade(color_scheme, -10); // Make the gradient slightly darker
    style_btn.body.radius = 10; // Round the corners a bit
    style_btn.text.color = LV_COLOR_WHITE; // White text on the button
    style_btn.body.border.color = LV_COLOR_WHITE; // White border for cool effect
    style_btn.body.border.width = 2; // Set the border width
    style_btn.body.shadow.color = LV_COLOR_SILVER; // Shadow effect for cool look
    style_btn.body.shadow.width = 5; // Set the shadow width
    style_btn.text.font = &lv_font_dejavu_20; // Set the font for the text

    // Create a style for the confirm button when it's pressed
    static lv_style_t style_btn_pr;
    lv_style_copy(&style_btn_pr, &style_btn); // Start with the released style
    style_btn_pr.body.main_color = color_shade(color_scheme, -30); // Darker color for pressed state
    style_btn_pr.body.grad_color = color_shade(color_scheme, -40); // Even darker for gradient
    style_btn_pr.text.color = color_shade(color_scheme, 50); // Lighter color for the text
    style_btn_pr.body.border.color = LV_COLOR_WHITE; // Keep the border color
    style_btn_pr.body.shadow.width = 3; // Smaller shadow for a "pressed" effect

    // Confirm button setup
    lv_obj_t *confirmBtn = lv_btn_create(scr, NULL);
    lv_btn_set_style(confirmBtn, LV_BTN_STYLE_REL, &style_btn); // Apply the released style to the button
    lv_btn_set_style(confirmBtn, LV_BTN_STYLE_PR, &style_btn_pr); // Apply the pressed style to the button
    lv_obj_set_size(confirmBtn, 120, 50); // Set the button size
    lv_obj_align(confirmBtn, scr, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10); // Align to the bottom-right with some margin

    // Assign the event handler to the confirm button
    lv_btn_set_action(confirmBtn, LV_BTN_ACTION_CLICK, confirm_btn_action);

    // Add a label to the confirm button
    lv_obj_t *confirmLabel = lv_label_create(confirmBtn, NULL);
    lv_label_set_text(confirmLabel, "Confirm");
    lv_label_set_style(confirmLabel, &style_btn); 

    return *confirmBtn;
}

lv_obj_t editPortsButton(lv_obj_t *scr, lv_color_t color_scheme) { 
    // Create a style for the confirm button
    static lv_style_t style_btn;
    lv_style_copy(&style_btn, &lv_style_btn_rel); // Copy a base button style to start with
    style_btn.body.main_color = color_scheme; // Use the passed color
    style_btn.body.grad_color = color_shade(color_scheme, -10); // Make the gradient slightly darker
    style_btn.body.radius = 10; // Round the corners a bit
    style_btn.text.color = LV_COLOR_WHITE; // White text on the button
    style_btn.body.border.color = LV_COLOR_WHITE; // White border for cool effect
    style_btn.body.border.width = 2; // Set the border width
    style_btn.body.shadow.color = LV_COLOR_SILVER; // Shadow effect for cool look
    style_btn.body.shadow.width = 5; // Set the shadow width
    style_btn.text.font = &lv_font_dejavu_20; // Set the font for the text

    // Create a style for the confirm button when it's pressed
    static lv_style_t style_btn_pr;
    lv_style_copy(&style_btn_pr, &style_btn); // Start with the released style
    style_btn_pr.body.main_color = color_shade(color_scheme, -30); // Darker color for pressed state
    style_btn_pr.body.grad_color = color_shade(color_scheme, -40); // Even darker for gradient
    style_btn_pr.text.color = color_shade(color_scheme, 50); // Lighter color for the text
    style_btn_pr.body.border.color = LV_COLOR_WHITE; // Keep the border color
    style_btn_pr.body.shadow.width = 3; // Smaller shadow for a "pressed" effect

    // Confirm button setup
    lv_obj_t *confirmBtn = lv_btn_create(scr, NULL);
    lv_btn_set_style(confirmBtn, LV_BTN_STYLE_REL, &style_btn); // Apply the released style to the button
    lv_btn_set_style(confirmBtn, LV_BTN_STYLE_PR, &style_btn_pr); // Apply the pressed style to the button
    lv_obj_set_size(confirmBtn, 120, 50); // Set the button size
    lv_obj_align(confirmBtn, scr, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10); // Align to the bottom-right with some margin

    // Assign the event handler to the confirm button
    lv_btn_set_action(confirmBtn, LV_BTN_ACTION_CLICK, confirm_btn_action);

    // Add a label to the confirm button
    lv_obj_t *confirmLabel = lv_label_create(confirmBtn, NULL);
    lv_label_set_text(confirmLabel, "Confirm");
    lv_label_set_style(confirmLabel, &style_btn); 

    return *confirmBtn;
}

Gif* gifContainer(lv_obj_t *scr) {
    // Create an outer container for positioning
    lv_obj_t *outer_gif_cont = lv_cont_create(scr, NULL);
    lv_obj_set_size(outer_gif_cont, LV_HOR_RES / 1.6, LV_VER_RES / 1.55);
    lv_obj_align(outer_gif_cont, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10);

    // Set the outer container's layout to off so its children can be freely moved
    lv_cont_set_layout(outer_gif_cont, LV_LAYOUT_OFF);

    // Now create and place the GIF inside the inner container
    textGif = new Gif("/usd/2145shake.gif", outer_gif_cont); // The Gif class constructor takes the file path and parent object
    return textGif;
}

void autonSelectorScreenInit(AutonFunction autonFunctions[], size_t autonCount, lv_color_t color_scheme) {
    chassisCalibrated = true;
    readSelectedAutonFromFile();
    // Create a style for the screen
    static lv_style_t style_scr;
    lv_style_copy(&style_scr, &lv_style_plain); // Start with a plain style
    style_scr.body.main_color = LV_COLOR_BLACK; // Set the main color to black
    style_scr.body.grad_color = LV_COLOR_BLACK; // Set the gradient color to black as well for a solid fill

    // Create a screen object
    lv_obj_t *scr = lv_obj_create(NULL, NULL);
    lv_obj_set_style(scr, &style_scr); // Apply the style to the screen object
    lv_scr_load(scr); // Load the screen

    autonList(scr, color_scheme, autonFunctions, autonCount);
    confirmButton(scr, color_scheme);

    // Load the screen
    lv_scr_load(scr);
}

void runSelectedAuton(AutonFunction autonFunctions[], size_t autonCount) {
    if(selectedAuton >= 0 && selectedAuton < autonCount) {
        autonFunctions[selectedAuton].function();
    } 
}
