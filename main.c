#include <gtk/gtk.h>

// Función para manejar el clic en los botones
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *button_text = gtk_button_get_label(GTK_BUTTON(widget));
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *current_text = gtk_entry_get_text(entry);

    // Concatenar el texto del botón al contenido actual
    gchar *new_text = g_strconcat(current_text, button_text, NULL);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}

// Función para calcular el resultado
static void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *expression = gtk_entry_get_text(entry);
    gdouble result;
    gchar buffer[50];

    // Evaluar la expresión (¡precaución: esto es básico y no seguro!)
    if (sscanf(expression, "%lf", &result) == 1) {
        snprintf(buffer, sizeof(buffer), "%.2f", result);
        gtk_entry_set_text(entry, buffer);
    } else {
        gtk_entry_set_text(entry, "Error");
    }
}

// Función para limpiar la entrada
static void on_clear_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    gtk_entry_set_text(entry, "");
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *entry, *button;
    gtk_init(&argc, &argv);

    // Crear ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crear grid (rejilla) para organizar los botones
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Campo de entrada (donde se ven los números)
    entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1); // Alinear a la derecha
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    // Texto de los botones (filas)
    const gchar *button_labels[16] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "C", "+"
    };

    // Crear botones y asignarles funciones
    for (int i = 0; i < 16; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_widget_set_size_request(button, 50, 50);

        // Conectar señales (eventos) según el botón
        if (g_strcmp0(button_labels[i], "=") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(on_calculate_clicked), entry);
        } else if (g_strcmp0(button_labels[i], "C") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(on_clear_clicked), entry);
        } else {
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);
        }

        // Posición del botón en el grid (fila, columna)
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, 1 + i / 4, 1, 1);
    }

    // Botón de "=" (resultado)
    button = gtk_button_new_with_label("=");
    gtk_widget_set_size_request(button, 50, 50);
    g_signal_connect(button, "clicked", G_CALLBACK(on_calculate_clicked), entry);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 5, 4, 1);

    // Mostrar todos los elementos
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
