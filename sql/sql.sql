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
        date_heure       Datetime NOT NULL ,
        co2              Integer ,
        chute            Bool ,
        temperature      Integer ,
        humidite         Integer ,
        four             Bool ,
        detection_alerte Bool ,
        id_chambre       Int NOT NULL ,
        PRIMARY KEY (date_heure ,id_chambre )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: seuil
#------------------------------------------------------------

CREATE TABLE seuil(
        id_seuil       int (11) Auto_increment  NOT NULL ,
        humiditymin    Integer ,
        humiditymax    Integer ,
        temperaturemin Integer ,
        temperaturemax Integer ,
        co2moyen       Integer ,
        co2haut        Integer ,
        four           Time ,
        id_chambre     Int NOT NULL ,
        PRIMARY KEY (id_seuil ,id_chambre )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: chambre
#------------------------------------------------------------

CREATE TABLE chambre(
        id_chambre   int (11) Auto_increment  NOT NULL ,
        ip_chambre   Varchar (25) ,
        port_chambre Integer ,
        PRIMARY KEY (id_chambre )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: contact
#------------------------------------------------------------

CREATE TABLE contact(
        login_email Varchar (25) NOT NULL ,
        full_name   Varchar (25) ,
        password    Varchar (25) ,
        PRIMARY KEY (login_email )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: capteurUser
#------------------------------------------------------------

CREATE TABLE capteurUser(
        temps  Datetime NOT NULL ,
        pas    Integer ,
        user   Varchar (25) ,
        numero Varchar (25) NOT NULL ,
        PRIMARY KEY (temps ,numero )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: telephone
#------------------------------------------------------------

CREATE TABLE telephone(
        numero           Varchar (25) NOT NULL ,
        ip_telephone     Varchar (25) ,
        port_telephone   Integer ,
        login_email_user Varchar (25) ,
        PRIMARY KEY (numero )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: seuil_user
#------------------------------------------------------------

CREATE TABLE seuil_user(
        id_seuil_user int (11) Auto_increment  NOT NULL ,
        deplacement   Datetime ,
        numero        Varchar (25) NOT NULL ,
        PRIMARY KEY (id_seuil_user ,numero )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: utilisateur_contact
#------------------------------------------------------------

CREATE TABLE utilisateur_contact(
        login_email      Varchar (25) NOT NULL ,
        login_email_user Varchar (25) NOT NULL ,
        PRIMARY KEY (login_email ,login_email_user )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: contact_chambre
#------------------------------------------------------------

CREATE TABLE contact_chambre(
        login_email Varchar (25) NOT NULL ,
        id_chambre  Int NOT NULL ,
        PRIMARY KEY (login_email ,id_chambre )
)ENGINE=InnoDB;

ALTER TABLE Utilisateur ADD CONSTRAINT FK_Utilisateur_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE capteur ADD CONSTRAINT FK_capteur_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE seuil ADD CONSTRAINT FK_seuil_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE capteurUser ADD CONSTRAINT FK_capteurUser_numero FOREIGN KEY (numero) REFERENCES telephone(numero);
ALTER TABLE telephone ADD CONSTRAINT FK_telephone_login_email_user FOREIGN KEY (login_email_user) REFERENCES Utilisateur(login_email_user);
ALTER TABLE seuil_user ADD CONSTRAINT FK_seuil_user_numero FOREIGN KEY (numero) REFERENCES telephone(numero);
ALTER TABLE utilisateur_contact ADD CONSTRAINT FK_utilisateur_contact_login_email FOREIGN KEY (login_email) REFERENCES contact(login_email);
ALTER TABLE utilisateur_contact ADD CONSTRAINT FK_utilisateur_contact_login_email_user FOREIGN KEY (login_email_user) REFERENCES Utilisateur(login_email_user);
ALTER TABLE contact_chambre ADD CONSTRAINT FK_contact_chambre_login_email FOREIGN KEY (login_email) REFERENCES contact(login_email);
ALTER TABLE contact_chambre ADD CONSTRAINT FK_contact_chambre_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
