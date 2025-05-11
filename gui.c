#include <gtk/gtk.h>

// This function is called when the application is launched
static void on_activate(GtkApplication *app, gpointer user_data)
{
    // Create a new window for the application
    GtkWidget *window = gtk_application_window_new(app);

    // Set the window title
    gtk_window_set_title(GTK_WINDOW(window), "Donkey Type");

    // Set default size: width = 500, height = 300
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

    // Create a vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Add the box to the window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a label
    GtkWidget *label = gtk_label_new("Donkey Type");

    // Make the label selectable (allows CSS color to apply)
    // gtk_label_set_selectable(GTK_LABEL(label), TRUE);

    // Center the label horizontally
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_START);  // Align to top

    // Add the label to the box
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 30);

    // Create label for dropdown
    GtkWidget *difficulty_label = gtk_label_new("Select Difficulty");

    // Create the dropdown
    GtkWidget *difficulty_dropdown = gtk_combo_box_text_new();
    gtk_widget_set_name(difficulty_dropdown, "difficulty-dropdown");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_dropdown), "Level 1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_dropdown), "Level 2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_dropdown), "Level 3");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_dropdown), "Level 4");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_dropdown), "Level 5");

    // Center the label and dropdown horizontally
    gtk_widget_set_halign(difficulty_label, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(difficulty_dropdown, GTK_ALIGN_CENTER);

    // Add the label and dropdown to the box
    gtk_box_pack_start(GTK_BOX(vbox), difficulty_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), difficulty_dropdown, FALSE, FALSE, 10);

    // Create CSS provider
    GtkCssProvider *provider = gtk_css_provider_new();

    // Load CSS data (set background color)
    // Load CSS rules:
    // - Set the label font to a code-like font ("Roboto Mono" if available)
    // - Set the font size to 20px
    // - Set the text color to bright green (#00FF00)
    // - Set the window background color to grey (for a terminal look)
    gtk_css_provider_load_from_data(provider,
        "label {"
        "   font-family: 'Courier Prime', monospace;"
        "   font-size: 20px;"
        "   color: #22FF22;"
        "   padding: 10px;"
        "}"
        ".difficulty-label {"
        "   color: #55FF55;"  // Slightly different green
        "}"
        "#difficulty-dropdown {"
        "   color: #22FF22;"
        "   background-color: #1e1e1e;"
        "   font-family: 'Courier Prime', monospace;"
        "   font-size: 16px;"
        "   padding: 5px;"
        "}"
        "window {"
        "   background-color: #121212;"
        "}",
        -1, NULL);
    
    // Get the style context of the window (needed to apply CSS)
    GtkStyleContext *context = gtk_widget_get_style_context(window);

    // Apply CSS to the window
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    // ALSO apply CSS to the label directly
    GtkStyleContext *label_context = gtk_widget_get_style_context(label);
    gtk_style_context_add_provider(label_context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // ALSO apply CSS to the difficulty label directly
    GtkStyleContext *difficulty_label_context = gtk_widget_get_style_context(difficulty_label);
    gtk_style_context_add_provider(difficulty_label_context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // ALSO apply CSS to the dropdown directly
    GtkStyleContext *dropdown_context = gtk_widget_get_style_context(difficulty_dropdown);
    gtk_style_context_add_provider(dropdown_context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Cleanup
    g_object_unref(provider);

    // Show the window
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    // Create a new GtkApplication
    GtkApplication *app = gtk_application_new("com.example.simplegtk", G_APPLICATION_DEFAULT_FLAGS);

    // Connect the "activate" signal to our function
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    // Run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Free the application memory
    g_object_unref(app);

    return status;
}
