FPVGate Documentation
Table des Matières

    Introduction
    Objectif du Projet
    Fonctionnalités Principales
    Composants Matériels
    Modes de Fonctionnement
    Communication entre les Portiques
    Interface Utilisateur
    Langage de Programmation et Environnement de Développement
    Bibliothèques et Dépendances
    Structure du Code
    Gestion des Événements
    Gestion des Données
    Tests et Validation
    Déploiement
    Gestion des Erreurs
    Performance et Optimisation
    Documentation et Support
    Conclusion

Introduction

FPVGate est un projet de système de portiques pour la détection de passage de drones (principalement des tinywhoops) utilisant des capteurs à ultrason. Ce système est conçu pour les courses de drones FPV (First Person View) et peut être utilisé comme ligne de départ et d'arrivée pour les courses. Le projet est destiné à un usage ludique et personnel, permettant aux utilisateurs de créer des circuits de course dans leur maison ou appartement.
Objectif du Projet

L'objectif principal de FPVGate est de fournir une solution pour créer des circuits de course de drones FPV à domicile. En plaçant des portiques (ou "gates") à différents endroits, les utilisateurs peuvent définir un tracé de circuit et chronométrer leurs temps de course, ce qui ajoute un objectif et un défi à leurs sessions de vol.
Fonctionnalités Principales

    Détection de Passage : Chaque portique est équipé d'un capteur à ultrason dirigé vers le haut pour détecter le passage d'un drone.
    Gestion des Temps de Course : Le système enregistre les temps de passage et les temps de course pour chaque tour.
    Configuration Flexible : Les portiques peuvent être placés n'importe où et configurés pour définir un tracé de circuit.
    Modes de Fonctionnement : Le système dispose de plusieurs modes de fonctionnement pour la calibration, la création de tracé, et la course.
    Communication WiFi : Les portiques communiquent entre eux via WiFi, avec un serveur web REST pour gérer les instructions et les notifications.

Composants Matériels

    Capteur Ultrason : HC-SR04
    Microcontrôleur : ESP32
    LED Strip : Pour indiquer l'état et le prochain portique à traverser
    Boutons : Pour la configuration et le contrôle
    Batteries : 18650 avec circuit de charge et régulation, ou alimentation 5V via micro USB
    Buzzer : Pour les notifications sonores
    Écran OLED : Pour l'interface utilisateur sur le portique Starter

Modes de Fonctionnement
IDLE

Mode par défaut où le portique attend des instructions.
CALIBRATION

Mode permettant de régler la distance de détection des capteurs à ultrason à l'aide d'un potentiomètre. Tous les portiques connectés passent en mode calibration.
TRACK

Mode permettant de créer le tracé du circuit. Les portiques enregistrent l'ordre de passage du drone.
RACE

Mode course où les portiques indiquent tour à tour le prochain portique à traverser et enregistrent les temps de course.
Communication entre les Portiques

Les portiques communiquent via WiFi. Le portique Starter crée un point d'accès WiFi avec un SSID et un mot de passe prédéfinis. Les autres portiques se connectent automatiquement à ce réseau et notifient le Starter de leur présence. Le Starter stocke les adresses IP des portiques pour leur envoyer des instructions. Les portiques connaissent l'adresse IP du Starter via la passerelle du réseau WiFi.
Interface Utilisateur

L'interface utilisateur est prévue sur un écran OLED sur le portique Starter. Cet écran permettra de configurer et de paramétrer le circuit. Aucune interface web ou application mobile n'est prévue pour l'instant.
Langage de Programmation et Environnement de Développement

Le projet est développé en C++ pour l'ESP32 en utilisant PlatformIO.
Bibliothèques et Dépendances

    Serveur Web : AsyncTCP et ESPAsyncWebServer
    Capteur à Ultrason : NewPin
    LED d'Indication : meirarc/Led ou gérée manuellement
    LED Strip : NeoPixel (pas encore implémenté)

Structure du Code

Le code est structuré en modules avec une classe dédiée pour chaque composant (capteur ultrason, LED, buzzer, etc.). Une partie serveur gère le portique Starter pour envoyer des instructions aux autres portiques.
Gestion des Événements

Les événements de détection de passage de drones sont gérés via des requêtes HTTP (POST). Lorsqu'un portique est en mode "listening", il envoie des impulsions jusqu'à détecter un passage et allume le ruban LED dans un pattern ou une couleur prédéfinie. Une fois le passage détecté, le portique notifie le Starter via un appel webservice. Le Starter donne ensuite l'ordre au prochain portique d'écouter.
Gestion des Données

Pour l'instant, aucune donnée n'est stockée de manière persistante. Les temps de course sont perdus lorsque le Starter est éteint. Étant donné l'usage ludique du projet et la flexibilité de la disposition des portiques, le stockage des temps n'est pas prioritaire.
Tests et Validation

Les tests unitaires et d'intégration ne sont pas encore implémentés. La méthode de test avec PlatformIO est encore à définir.
Déploiement

Le déploiement est actuellement effectué en branchant les ESP32 en série et en flasant le firmware. L'OTA (Over-The-Air) est envisagé pour simplifier les mises à jour, mais ce n'est pas encore une priorité.
Gestion des Erreurs

Aucun mécanisme de gestion des erreurs ou de journalisation n'est prévu pour l'instant.
Performance et Optimisation

La latence de communication via WiFi et les webservices REST doit être relativement basse pour permettre une détection rapide et une notification efficace entre les portiques. La fréquence des impulsions des capteurs à ultrason doit être suffisamment élevée pour détecter les petits drones en mouvement rapide.
Documentation et Support

Le projet sera documenté sur GitHub. La documentation sera complétée au fur et à mesure de l'avancement du projet. L'analyse actuelle et ces questions/réponses serviront de base à la rédaction de la documentation.
Conclusion

FPVGate est un projet innovant qui permet aux utilisateurs de créer des circuits de course de drones FPV à domicile. En utilisant des capteurs à ultrason et une communication WiFi, le système offre une solution flexible et ludique pour les amateurs de drones. Cette documentation fournit une vue d'ensemble complète et détaillée du projet, couvrant tous les aspects techniques et fonctionnels.