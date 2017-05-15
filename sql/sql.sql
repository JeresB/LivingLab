#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------


#------------------------------------------------------------
# Table: Utilisateur
#------------------------------------------------------------

CREATE TABLE Utilisateur(
        login_email_user Varchar (25) NOT NULL ,
        password         Varchar (25) ,
        full_name        Varchar (25) ,
        id_chambre       Int ,
        PRIMARY KEY (login_email_user )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: capteur
#------------------------------------------------------------

CREATE TABLE capteur(
        date_heure  TimeStamp NOT NULL ,
        co2         Integer ,
        chute       Bool ,
        temperature Integer ,
        humidite    Integer ,
        four        Bool ,
        id_chambre  Int NOT NULL ,
        PRIMARY KEY (date_heure ,id_chambre )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: seuil
#------------------------------------------------------------

CREATE TABLE seuil(
        user             Varchar (25) NOT NULL ,
        humiditymin      Integer ,
        humiditymax      Integer ,
        temperaturemin   Integer ,
        temperaturemax   Integer ,
        co2moyen         Integer ,
        co2haut          Integer ,
        four             Time ,
        login_email_user Varchar (25) NOT NULL ,
        PRIMARY KEY (user ,login_email_user )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: chambre
#------------------------------------------------------------

CREATE TABLE chambre(
        id_chambre int (11) Auto_increment  NOT NULL ,
        ip_chambre Varchar (25) ,
        PRIMARY KEY (id_chambre )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: contact
#------------------------------------------------------------

CREATE TABLE contact(
        login_email Varchar (25) NOT NULL ,
        password    Varchar (25) ,
        PRIMARY KEY (login_email )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: capteurUser
#------------------------------------------------------------

CREATE TABLE capteurUser(
        temps      TimeStamp NOT NULL ,
        pas        Integer ,
        user       Varchar (25) ,
        id_chambre Int NOT NULL ,
        PRIMARY KEY (temps ,id_chambre )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: contact_chambre
#------------------------------------------------------------

CREATE TABLE contact_chambre(
        login_email Varchar (25) NOT NULL ,
        id_chambre  Int NOT NULL ,
        PRIMARY KEY (login_email ,id_chambre )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: utilisateur_contact
#------------------------------------------------------------

CREATE TABLE utilisateur_contact(
        login_email      Varchar (25) NOT NULL ,
        login_email_user Varchar (25) NOT NULL ,
        PRIMARY KEY (login_email ,login_email_user )
)ENGINE=InnoDB;

ALTER TABLE Utilisateur ADD CONSTRAINT FK_Utilisateur_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE capteur ADD CONSTRAINT FK_capteur_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE seuil ADD CONSTRAINT FK_seuil_login_email_user FOREIGN KEY (login_email_user) REFERENCES Utilisateur(login_email_user);
ALTER TABLE capteurUser ADD CONSTRAINT FK_capteurUser_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE contact_chambre ADD CONSTRAINT FK_contact_chambre_login_email FOREIGN KEY (login_email) REFERENCES contact(login_email);
ALTER TABLE contact_chambre ADD CONSTRAINT FK_contact_chambre_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE utilisateur_contact ADD CONSTRAINT FK_utilisateur_contact_login_email FOREIGN KEY (login_email) REFERENCES contact(login_email);
ALTER TABLE utilisateur_contact ADD CONSTRAINT FK_utilisateur_contact_login_email_user FOREIGN KEY (login_email_user) REFERENCES Utilisateur(login_email_user);
