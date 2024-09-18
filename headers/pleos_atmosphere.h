//******************
//
// pleos_data_structure.h
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
// This file contains the page of the Atmosphere plugin.
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

#ifndef PLEOS_ATMOSPHERE
#define PLEOS_ATMOSPHERE

// Include SCLS Graphic Benoit
#include "../../../scls-graphic-benoit/scls_graphic.h"

// The namespace "pleos" is used to simplify the all.
namespace pleos {

    class Atmosphere_Page : public scls::GUI_Page {
        // Class representating the atmosphere page for PLEOS

    public:

        // Data_Structure_Page constructor
        Atmosphere_Page(scls::_Window_Advanced_Struct* window_struct, std::string name);
        // Loads an object in a page from XML
        virtual std::shared_ptr<scls::GUI_Object> __create_loaded_object_from_type(std::string object_name, std::string object_type, scls::GUI_Object* parent);

        // Displays the atmospheric composition page
        void display_composition_page();
        // Displays the home page
        void display_home_page();
        // Hide everything in the page
        void hide_all();

        // Checks the composition events
        void check_composition_events();
        // Checks the navigation events
        void check_navigation_events();
        // Checks the tropospheric events
        void check_tropospheric_events();
        // Update the events in the page
        virtual void update_event();

        //******************
        //
        // "Atmosphere composition" page handle
        //
        //******************

        // Loads the tropospheric composition page
        void load_tropospheric_composition_page();
        // Loads the tropospheric description page
        void load_tropospheric_description_page();
        // Loads the tropospheric page
        void load_tropospheric_page();

        // Unloads the tropospheric page
        void unload_composition_layer_navigation(){a_composition_layer_navigation_buttons.clear();a_composition_layer_navigation.get()->reset();};

    private:

        // Struct representating the current state of the page
        struct {
            #define PLEOS_ATMOSPHERE_HOME 0
            #define PLEOS_ATMOSPHERE_COMPOSITION 0

            // Current page of the software
            unsigned int current_page = PLEOS_ATMOSPHERE_HOME;

            #define PLEOS_ATMOSPHERE_COMPOSITION_TROPOSPHERIC 0

            // Current atmosphere of the atmospheric page software
            unsigned int current_composition_atmosphere = PLEOS_ATMOSPHERE_COMPOSITION_TROPOSPHERIC;
        } a_current_state;

        // GUI Stuffs

        // Page bodies

        // "Atmosphere composition" body
        std::shared_ptr<scls::GUI_Object> a_composition_body;
        // "Atmosphere composition" layer navigation
        std::shared_ptr<scls::GUI_Scroller> a_composition_layer_navigation;
        std::vector<std::shared_ptr<scls::GUI_Text>> a_composition_layer_navigation_buttons;
        // Home body
        std::shared_ptr<scls::GUI_Object> a_home_body;

        // Composition page buttons

        // "Atmosphere composition" bottom button
        std::shared_ptr<scls::GUI_Object> a_composition_bottom_button;
        // "Atmosphere composition" top button
        std::shared_ptr<scls::GUI_Object> a_composition_top_button;

        // Navigation buttons

        // "Atmosphere composition" navigation button
        std::shared_ptr<scls::GUI_Text> a_navigation_composition;
        // Home navigation button
        std::shared_ptr<scls::GUI_Text> a_navigation_home;

        // Text and text input

        // "Atmosphere composition" content text
        std::shared_ptr<scls::GUI_Text> a_composition_layer_content;
    };

    class __Temp_Pleos_Window : public scls::Window {
        // Temporary used window by PLEOS
    public :
        // __Temp_Pleos_Window constructor
        __Temp_Pleos_Window(unsigned int w, unsigned int h, std::string path) : scls::Window(w, h, path) { set_window_title("PLEOS - Atmosphère"); }

        // Create an object in the window
        std::shared_ptr<scls::Object> __create_loaded_object_from_type(std::string object_name, std::string object_type) {
            if(object_name == "atmosphere_page") {
                std::shared_ptr<Atmosphere_Page> hub = *new_page_2d<Atmosphere_Page>(object_name);

                // Return the good object
                std::shared_ptr<scls::Object> to_return = hub;
                return to_return;
            } return scls::Window::__create_loaded_object_from_type(object_name, object_type);
        }
    };
}

#endif // PLEOS_ATMOSPHERE
