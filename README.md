# project-PA
Library Management System in C



Ce projet est un système de gestion de bibliothèque simple écrit en C. Il permet de gérer les utilisateurs et les livres au sein de la bibliothèque. Les fonctionnalités incluent l'enregistrement des utilisateurs, la connexion, et les opérations CRUD (Create, Read, Update, Delete) pour les livres. Les utilisateurs ont des rôles spécifiques : Administrateur ou Membre, avec des privilèges différents.

Fonctionnalités:

Utilisateurs

    Enregistrement : Permet aux nouveaux utilisateurs de s'inscrire avec un nom d'utilisateur, un mot de passe et un rôle (Admin ou Member).
    Connexion : Permet aux utilisateurs de se connecter en utilisant leur nom d'utilisateur et leur mot de passe.
    Rôles :
        Admin : Peut ajouter, afficher et supprimer des livres.
        Member : Peut seulement afficher et emprunter des livres.

Livres

    Ajouter un livre (Admin) : Ajouter de nouveaux livres avec un identifiant, un titre, un auteur, un prix et une quantité.
    Afficher les livres (Admin et Member) : Voir la liste de tous les livres disponibles.
    Supprimer un livre (Admin) : Supprimer des livres du système.
    Emprunter un livre (Member) : Emprunter des livres, ce qui réduit la quantité en stock.

