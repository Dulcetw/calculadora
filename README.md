Instalar gtk
sudo apt-get install libgtk-3-dev

Compilar

gcc calculadora_gui.c -o calculadora_gui `pkg-config --cflags --libs gtk+-3.0`

ejecutar

./calculadora_gui
