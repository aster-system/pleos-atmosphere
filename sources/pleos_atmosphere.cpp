//******************
//
// pleos_atmosphere.cpp
//
//******************
// Presentation :
//
// PLEOS, by Aster System, is a project which aims education.
// By using the power of SCLS and other Aster System's tools, we created  this.
// We want to make education easier for everyone (teachers, as students and pupils).
// The software is made in french, because the main goal is France educational system.
// For more information, see : https://aster-system.github.io/aster-system/projects/pleos.html.
//
// The "Atmosphere" part aims science lesson.
// Its goal is to explain how the atmosphere works, easily for everyone.
//
// This file contains the source code of "pleos_atmosphere.h".
//
//******************
//
// License (GPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of PLEOS.
// PLEOS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// PLEOS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with PLEOS. If not, see <https://www.gnu.org/licenses/>.
//

// Include the source code
#include "../headers/pleos_atmosphere.h"

// The namespace "pleos" is used to simplify the all.
namespace pleos {

    // Data_Structure_Page constructor
    Atmosphere_Page::Atmosphere_Page(scls::_Window_Advanced_Struct* window_struct, std::string name) : GUI_Page(window_struct, name) {

    };

    // Loads an object in a page from XML
    std::shared_ptr<scls::GUI_Object> Atmosphere_Page::__create_loaded_object_from_type(std::string object_name, std::string object_type, scls::GUI_Object* parent) {
        if(object_name == "atmosphere_composition_body") {
            a_composition_body = *parent->new_object<scls::GUI_Object>(object_name);
            return a_composition_body;
        }
        else if(object_name == "atmosphere_composition_body_layer_bottom") {
            a_composition_bottom_button = *parent->new_object<scls::GUI_Object>(object_name);
            return a_composition_bottom_button;
        }
        else if(object_name == "atmosphere_composition_body_layer_content") {
            a_composition_layer_content = *parent->new_object<scls::GUI_Text>(object_name);
            return a_composition_layer_content;
        }
        else if(object_name == "atmosphere_composition_body_layer_navigation") {
            a_composition_layer_navigation = *parent->new_object<scls::GUI_Scroller>(object_name);
            return a_composition_layer_navigation;
        }
        else if(object_name == "atmosphere_composition_body_layer_top") {
            a_composition_top_button = *parent->new_object<scls::GUI_Object>(object_name);
            return a_composition_top_button;
        }
        else if(object_name == "atmosphere_home_body") {
            a_home_body = *parent->new_object<scls::GUI_Object>(object_name);
            return a_home_body;
        }
        else if(object_name == "atmosphere_navigation_composition") {
            a_navigation_composition = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_composition;
        }
        else if(object_name == "atmosphere_navigation_home") {
            a_navigation_home = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_home;
        }

        // Classic object creation
        return GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    }

    // Checks the composition events
    void Atmosphere_Page::check_composition_events() {
        // Tropospheric page
        if(a_current_state.current_composition_atmosphere == PLEOS_ATMOSPHERE_COMPOSITION_TROPOSPHERIC) check_tropospheric_events();
    }

    // Checks the navigation events
    void Atmosphere_Page::check_navigation_events() {
        if(a_navigation_composition.get() != 0 && a_navigation_composition.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Display the "Atmosphere composition" page
            display_composition_page();
        }
        if(a_navigation_home.get() != 0 && a_navigation_home.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // Display the home page
            display_home_page();
        }
    }

    // Checks the tropospheric events
    void Atmosphere_Page::check_tropospheric_events() {
        for(int i = 0;i<static_cast<int>(a_composition_layer_navigation_buttons.size());i++) {
            if(a_composition_layer_navigation_buttons[i].get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                if(i == 0) load_tropospheric_description_page();
                else if(i == 1) load_tropospheric_composition_page();
            }
        }
    }

    // Displays the atmospheric composition page
    void Atmosphere_Page::display_composition_page() {
        hide_all();
        if(a_composition_body.get() != 0) a_composition_body.get()->set_visible(true);

        // Load the needed datas
        a_current_state.current_page = PLEOS_ATMOSPHERE_COMPOSITION;
        load_tropospheric_page();
    }

    // Displays the home page
    void Atmosphere_Page::display_home_page() {
        hide_all();
        if(a_home_body.get() != 0) a_home_body.get()->set_visible(true);

        // Load the needed datas
        a_current_state.current_page = PLEOS_ATMOSPHERE_HOME;
    }

    // Hide everything in the page
    void Atmosphere_Page::hide_all() {
        if(a_composition_body.get() != 0) a_composition_body.get()->set_visible(false);
        if(a_home_body.get() != 0) a_home_body.get()->set_visible(false);
    }

    // Update the events in the page
    void Atmosphere_Page::update_event() {
        GUI_Page::update_event();

        check_navigation_events();

        // Composition page
        if(a_current_state.current_page == PLEOS_ATMOSPHERE_COMPOSITION) check_composition_events();
    }

    //******************
    //
    // "Atmosphere composition" page handle
    //
    //******************

    // Loads the tropospheric composition page
    void Atmosphere_Page::load_tropospheric_composition_page() {
        // Set the needed text
        // Sources : https://www.projetecolo.com/troposphere-definition-caracteristiques-et-importance-503.html
        //           https://www.aeronomie.be/fr/encyclopedie/troposphere-gaz-dominants-composition-abondance
        std::string final_text = "En général, ce que l'on appelle la \"composition de l'atmosphère\"</br>";
        final_text += "est en fait la composition de la troposphère seule. Elle ne varie</br>";
        final_text += "donc pas des valeurs bien connues : 78% de diazote, 21% de dioxygène</br>";
        final_text += "et 1% des autres gaz.</br></br>";
        final_text += "Ces 1% peuvent sembler négligeables, mais sont cependant ce qui provoque</br>";
        final_text += "les caractéristiques actuelles de l'atmosphère. On y retrouve tout type</br>";
        final_text += "de gaz, comme les communs vapeur d'eau et dioxyde de carbone, ou bien des</br>";
        final_text += "gaz plus exotiques, comme du dioxyde d'azote NO2. Elle contient aussi un</br>";
        final_text += "morceau de la célèbre couche d'ozone (environ 10%).</br>";
        a_composition_layer_content.get()->set_font_size(30);
        a_composition_layer_content.get()->set_text(scls::to_utf_8_code_point(final_text));
    }

    // Loads the tropospheric description page
    void Atmosphere_Page::load_tropospheric_description_page() {
        // Set the needed text
        // Sources : https://www.aeronomie.be/fr/encyclopedie/troposphere-pourquoi-couche-atmospherique-importante
        std::string final_text = "La troposphère est la couche la plus basse de l'atmosphère, allant</br>";
        final_text += "de 0 à entre 8km au pôle et 17km à l'équateur de la surface. Elle</br>";
        final_text += "représente à elle toute seule 85% de la masse de l'atmosphère. En</br>";
        final_text += "effet, en tant que couche la plus basse, elle est plus soumise à la</br>";
        final_text += "gravité, et donc concentre plus de matière, soumise à plus de pression.</br></br>";
        final_text += "Plus on monte en altitude, plus la pression diminue, plus la température</br>";
        final_text += "baisse (environ 6° par kilomètre). Cette différence de température est</br>";
        final_text += "responsable d'un phénomène de monté de l'air chaud et descente de l'air</br>";
        final_text += "froid : la convection de l'air. Ce genre de phénomène rend cette couche</br>";
        final_text += "très dynamique, et propice à un phénomène très spécial : la météo.</br>";
        a_composition_layer_content.get()->set_font_size(30);
        a_composition_layer_content.get()->set_text(scls::to_utf_8_code_point(final_text));
    }

    // Loads the tropospheric page
    void Atmosphere_Page::load_tropospheric_page() {
        unload_composition_layer_navigation();

        // Create the description button
        std::shared_ptr<scls::GUI_Text> home_button = *a_composition_layer_navigation.get()->new_object<scls::GUI_Text>("atmosphere_composition_layer_navigation-description");
        home_button.get()->set_border_width_in_pixel(1);
        home_button.get()->set_font_size(40);
        home_button.get()->set_height_in_pixel(50);
        home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        home_button.get()->set_text("Description");
        home_button.get()->set_texture_alignment(scls::Alignment_Texture::T_Fit);
        home_button.get()->set_width_in_scale(1);
        home_button.get()->set_x_in_scale(0);
        home_button.get()->set_y_in_scale(0);
        a_composition_layer_navigation_buttons.push_back(home_button);

        // Create the composition button
        home_button = *a_composition_layer_navigation.get()->new_object<scls::GUI_Text>("atmosphere_composition_layer_navigation-composition");
        home_button.get()->set_border_width_in_pixel(1);
        home_button.get()->set_font_size(40);
        home_button.get()->set_height_in_pixel(50);
        home_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        home_button.get()->set_text("Composition");
        home_button.get()->set_texture_alignment(scls::Alignment_Texture::T_Fit);
        home_button.get()->set_width_in_scale(1);
        home_button.get()->set_x_in_scale(0);
        home_button.get()->set_y_in_scale(0);
        a_composition_layer_navigation_buttons.push_back(home_button);

        if(a_composition_layer_navigation_buttons.size() > 0) {
            // Place the buttons
            std::shared_ptr<scls::GUI_Text> last_button = a_composition_layer_navigation_buttons[a_composition_layer_navigation_buttons.size() - 1];
            last_button.get()->attach_bottom_in_parent();
            for(int i = 1;i<static_cast<int>(a_composition_layer_navigation_buttons.size());i++) {
                unsigned int current_i = a_composition_layer_navigation_buttons.size() - (i + 1);
                a_composition_layer_navigation_buttons[current_i].get()->attach_top_of_object_in_parent(last_button);
                last_button = a_composition_layer_navigation_buttons[current_i];
            }
        }

        // Finalize the creation
        a_composition_layer_navigation.get()->check_scroller();
        a_current_state.current_composition_atmosphere = PLEOS_ATMOSPHERE_COMPOSITION_TROPOSPHERIC;
        load_tropospheric_description_page();

        // Handle top / bottom buttons
        a_composition_bottom_button.get()->set_visible(false);
        a_composition_top_button.get()->set_visible(true);
    }
}
