# Object files
OBJ_FILES = main.o create_index.o create_database.o display_database.o save_database.o search.o update.o free_all.o
# Output executable
TARGET = Inverter_search.exe

$(TARGET): $(OBJ_FILES)
	gcc -o $(TARGET) $(OBJ_FILES)
# Compile main.o
main.o: main.c
	gcc -c main.c

# Compile common.o
create_index.o: create_index.c
	gcc -c create_index.c

# compile create_database.o
create_database.o: create_database.c
	gcc -c create_database.c

#compile display.o
display_database.o: display_database.c
	gcc -c display_database.c

#compile savedatabase.o
save_database.o: save_database.c
	gcc -c save_database.c

#compile search.o
search.o: search.c
	gcc -c search.c

#compile update.o
update.o: update.c
	gcc -c update.c

#compile free_all.o
free_all.o: free_all.c
	gcc -c free_all.c
# Clean up object files and executable
clean:
	rm -f $(OBJ_FILES) $(TARGET)
