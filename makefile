
#le compilateur c utilisé
CC = gcc

#les options à la compilations
OPTIONS = -Wall -Wextra

#le nom du programme
NAME = roguelike

#le nom du dossier contenant les fichiers .o générés lors de la compilation
ODIR = o

#le nom du dossier contenant les sources
SRCDIR = src

#le nom du dossier contenant les sources des tests
TESTDIR = test

#le nom du dossier contenant la documentation
DOCDIR = doc


#lance la génération du ficher executable final, necessite la compilation des .o avant
compile: compile_o
	$(CC) $(OPTIONS) ./$(ODIR)/$(SRCDIR)/*.o -o $(NAME).exe

#compilation des fichiers .o
compile_o:
	#création du dossier
	mkdir -p ./$(ODIR)/$(SRCDIR)
	#on lance gcc depuis ce dossier pour que les .o soient créés dans celui-ci
	cd ./$(ODIR)/$(SRCDIR); $(CC) $(OPTIONS) -c ./../../$(SRCDIR)/*.c

#génère le fichier executable des tests, en liant les .o des tests et du programme, sauf le main qui ne contient que la fonction princiale du programme
test: test_o
	$(CC) $(OPTIONS) ./$(ODIR)/$(TESTDIR)/*.o -lcunit -o $(NAME)_test.exe

#compile les .o des tests
test_o:
	mkdir -p ./$(ODIR)/$(TESTDIR)
	cd ./$(ODIR)/$(TESTDIR); $(CC) $(OPTIONS) -c ./../../$(TESTDIR)/*.c ./../../$(SRCDIR)/*.c
	cd ./$(ODIR)/$(TESTDIR); rm main.o

#lance les tests après les avoir compilés
runtest: test
	./$(NAME)_test.exe

#lance le programme juste après l'avoir compilé
run: compile
	./$(NAME).exe

#lance la compilation spécialement pour le déboguage puis gdb
debug: clean debug_o
	$(CC) $(OPTIONS) $(ODIR)/$(SRCDIR)/*.o -o $(NAME).exe
	gdb -e $(NAME).exe
	
#compilation des .o pour le déboguage avec l'option -g
debug_o:
	mkdir -p ./$(ODIR)/$(SRCDIR)
	cd ./$(ODIR)/$(SRCDIR); $(CC) $(OPTIONS) -g -c ./../../$(SRCDIR)/*.c

#nettoie le projet des fichiers créés lors de la compilation
clean:
	rm -rf ./$(ODIR)
	rm -f ./*.exe
	rm -f ./*.exe

#génère la documentation
docgen:
	rm -rf ./$(DOCDIR)
	mkdir ./$(DOCDIR)
	doxygen

#copie la documentation générée dans le dossier nom_utilisateur/public_html/nom_projet, et change leur permissions pour les rendre lisibles par tous, ainsi, si cette command est lancée depuis un ordinateur de l'université, la documentation sera mise à jour et consultables à l'adresse http://info.univ-lemans.fr/~nom_utilisateur/roguelike/index.html
docpost: docgen
	rm -rf ~/public_html/$(NAME)
	mkdir -p ~/public_html/$(NAME)
	cp -R $(DOCDIR)/html/* ~/public_html/$(NAME)
	chmod -R 755 ~/public_html/$(NAME)

all: clean compile runtest docpost

commit: clean
	git add *
	git commit -a