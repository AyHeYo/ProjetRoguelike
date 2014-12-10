void generer() {
    int i, j, n_salles, s;
    Rectangle * salles;
    for (i = 0 ; i < TAILLE ; i++) {
        for (j = 0 ; j < TAILLE ; j++) {
            labyrinthe[i][j] = MUR;
        }
    }
    n_salles = random2(3, lab_dim.l2 / 5);
    salles = (Rectangle *) malloc(n_salles * sizeof(Rectangle));
    if (random2(0, 1)) {
        salles[0].l1 = lab_dim.l1 + 1;
        salles[0].c1 = random2(lab_dim.c1 + 1, lab_dim.c2 / 4);
    } else {
        salles[0].l1 = random2(lab_dim.l1 + 1, lab_dim.l2 / 4);
        salles[0].c1 = lab_dim.c1 + 1;
    }
    salles[0].l2 = random2(salles[0].l1 + 4, salles[0].l1 + lab_dim.l2 / 3);
    salles[0].c2 = random2(salles[0].c1 + 4, salles[0].c1 + lab_dim.c2 / 3);
    for (s = 0 ; s <= 0 ; s++) {
        for (i = salles[0].l1 ; i < salles[0].l2 ; i++) {
            for (j = salles[0].c1 ; j < salles[0].c2 ; j++) {
                labyrinthe[i][j] = VIDE;
            }
        }
    }
}
