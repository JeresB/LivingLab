#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------

ALTER DATABASE CHARACTER SET utf8 COLLATE utf8_general_ci;

#------------------------------------------------------------
# Table: Utilisateur
#------------------------------------------------------------

CREATE TABLE Utilisateur(
        login_email_user Varchar (80) NOT NULL ,
        password         Varchar (25) ,
        first_name       Varchar (30) ,
        last_name        Varchar (30) ,
        id_chambre       Int ,
        id_telephone     Int ,
        PRIMARY KEY (login_email_user )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: capteur
#------------------------------------------------------------

CREATE TABLE capteur(
        date_heure       TimeStamp NOT NULL ,
        co2              Integer ,
        chute            Bool ,
        temperature      Float ,
        humidite         Integer ,
        four             Bool ,
        presence         Varchar (80) ,
        detection_alerte Varchar (255) ,
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
        login_email Varchar (80) NOT NULL ,
        password    Varchar (25) ,
        first_name  Varchar (30) ,
        last_name   Varchar (30) ,
        PRIMARY KEY (login_email )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: capteurUser
#------------------------------------------------------------

CREATE TABLE capteurUser(
        temps                 TimeStamp NOT NULL ,
        pas                   Integer ,
        user                  Varchar (80) ,
        detection_alerte_user Varchar (255) ,
        id_telephone          Int NOT NULL ,
        PRIMARY KEY (temps ,id_telephone )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: telephone
#------------------------------------------------------------

CREATE TABLE telephone(
        id_telephone   int (11) Auto_increment  NOT NULL ,
        numero         Varchar (25) NOT NULL ,
        ip_telephone   Varchar (25) ,
        port_telephone Integer ,
        PRIMARY KEY (id_telephone )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: seuil_user
#------------------------------------------------------------

CREATE TABLE seuil_user(
        id_seuil_user int (11) Auto_increment  NOT NULL ,
        deplacement   Time ,
        id_telephone  Int NOT NULL ,
        PRIMARY KEY (id_seuil_user ,id_telephone )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: utilisateur_contact
#------------------------------------------------------------

CREATE TABLE utilisateur_contact(
        login_email      Varchar (80) NOT NULL ,
        login_email_user Varchar (80) NOT NULL ,
        PRIMARY KEY (login_email ,login_email_user )
)ENGINE=InnoDB;

ALTER TABLE Utilisateur ADD CONSTRAINT FK_Utilisateur_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE Utilisateur ADD CONSTRAINT FK_Utilisateur_id_telephone FOREIGN KEY (id_telephone) REFERENCES telephone(id_telephone);
ALTER TABLE capteur ADD CONSTRAINT FK_capteur_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE seuil ADD CONSTRAINT FK_seuil_id_chambre FOREIGN KEY (id_chambre) REFERENCES chambre(id_chambre);
ALTER TABLE capteurUser ADD CONSTRAINT FK_capteurUser_id_telephone FOREIGN KEY (id_telephone) REFERENCES telephone(id_telephone);
ALTER TABLE seuil_user ADD CONSTRAINT FK_seuil_user_id_telephone FOREIGN KEY (id_telephone) REFERENCES telephone(id_telephone);
ALTER TABLE utilisateur_contact ADD CONSTRAINT FK_utilisateur_contact_login_email FOREIGN KEY (login_email) REFERENCES contact(login_email);
ALTER TABLE utilisateur_contact ADD CONSTRAINT FK_utilisateur_contact_login_email_user FOREIGN KEY (login_email_user) REFERENCES Utilisateur(login_email_user);



ALTER TABLE Utilisateur MODIFY password varchar(25) CHARACTER SET utf8 COLLATE utf8_bin;
ALTER TABLE contact MODIFY password varchar(25) CHARACTER SET utf8 COLLATE utf8_bin;
ALTER TABLE capteur CHANGE date_heure date_heure TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;


INSERT INTO telephone (id_telephone, numero, ip_telephone, port_telephone) VALUES (1, 0123456789, '192.168.199.30', 1001);
INSERT INTO telephone (id_telephone, numero, ip_telephone, port_telephone) VALUES (2, 0987654321, '192.168.199.31', 1001);

INSERT INTO chambre (id_chambre, ip_chambre, port_chambre) VALUES (1, '192.168.199.30', 1000);
INSERT INTO chambre (id_chambre, ip_chambre, port_chambre) VALUES (2, '192.168.199.31', 1000);

INSERT INTO Utilisateur (login_email_user, password, first_name, last_name, id_chambre, id_telephone) VALUES ('Chuck.Norris@isen-ouest.yncrea.fr', 'texas-ranger', 'Chuck', 'Norris', 1, 1);
INSERT INTO Utilisateur (login_email_user, password, first_name, last_name, id_chambre, id_telephone) VALUES ('Steven.Seagal@isen-ouest.yncrea.fr', '1234', 'Steven', 'Seagal', 2, 2);

INSERT INTO contact (login_email, password, first_name, last_name) VALUES ('Bruce.lee@isen-ouest.yncrea.fr', 'un-livre', 'Bruce', 'Lee');
INSERT INTO contact (login_email, password, first_name, last_name) VALUES ('Michel.Seagal@isen-ouest.yncrea.fr', '456', 'Michel', 'Seagal');

INSERT INTO utilisateur_contact (login_email, login_email_user) VALUES ('Bruce.Lee@isen-ouest.yncrea.fr', 'Chuck.Norris@isen-ouest.yncrea.fr');
INSERT INTO utilisateur_contact (login_email, login_email_user) VALUES ('Michel.Seagal@isen-ouest.yncrea.fr', 'Steven.Seagal@isen-ouest.yncrea.fr');

INSERT INTO seuil (id_seuil, humiditymin, humiditymax, temperaturemin, temperaturemax, co2moyen, co2haut, four, id_chambre) VALUES (1, 35, 70, 17, 29, 1000, 1500, '02:00:00', 1);
INSERT INTO seuil (id_seuil, humiditymin, humiditymax, temperaturemin, temperaturemax, co2moyen, co2haut, four, id_chambre) VALUES (2, 35, 70, 17, 29, 1000, 1500, '02:00:00', 2);

INSERT INTO seuil_user (id_seuil_user, deplacement, id_telephone) VALUES (1, '04:00:00', 1);
INSERT INTO seuil_user (id_seuil_user, deplacement, id_telephone) VALUES (2, '04:00:00', 2);

INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:44:43', '263', '0', '19.1', '77', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', 'Humidité supérieur au seuil autorisé !!! ', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:45:43', '345', '0', '19', '71', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', 'Humidité supérieur au seuil autorisé !!! ', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:46:43', '280', '0', '15.1', '73', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', 'La température est trop basse !!! Humidité supérieur au seuil autorisé !!! ', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:47:43', '279', '0', '19.3', '67', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', '', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:48:43', '305', '0', '19.1', '71', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', 'Humidité supérieur au seuil autorisé !!! ', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:49:43', '285', '0', '22.6', '69', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', '', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:50:43', '247', '0', '19.5', '69', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', '', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:51:43', '247', '0', '17.4', '69', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', '', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:52:43', '244', '0', '19.8', '65', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', '', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:53:43', '312', '0', '17.6', '70', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', '', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:54:43', '275', '0', '20.2', '75', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', 'Humidité supérieur au seuil autorisé !!! ', '1');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:55:43', '283', '0', '16.8', '71', '0', 'Chuck.Norris@isen-ouest.yncrea.fr', 'La température est trop basse !!! Humidité supérieur au seuil autorisé !!! ', '1');


INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:47:48', '1074', '0', '22.3', '51', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:48:48', '1092', '0', '21.4', '45', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:49:48', '1021', '0', '21', '55', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:50:48', '1090', '0', '21.6', '47', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:51:48', '1086', '0', '19.9', '52', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:52:48', '1087', '0', '20.9', '47', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:53:48', '1017', '0', '22.4', '46', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! La température a évoluée dangereusement pendant les 5 dernières minutes !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:54:48', '1099', '0', '21.2', '46', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:55:48', '1108', '0', '21.4', '48', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:56:48', '1093', '0', '21.4', '56', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:57:48', '1102', '0', '20.6', '45', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');
INSERT INTO capteur (date_heure, co2, chute, temperature, humidite, four, presence, detection_alerte, id_chambre) VALUES ('2017-05-29 11:58:48', '1098', '0', '21.6', '49', '0', 'Steven.Seagal@isen-ouest.yncrea.fr', 'Le co2 a atteint un niveau dangereux !!! ', '2');

INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 13:00:00', 500, 'chuck norris', '', 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 14:00:00', 46, 'chuck norris', '', 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 15:00:00', 0, 'chuck norris', '', 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 16:00:00', 0, 'chuck norris', '', 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 17:00:00', 0, 'chuck norris', '', 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 18:00:00', 0, 'chuck norris', "L'utilisateur est immobile depuis trop longtemps !!!", 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 19:00:00', 180, 'chuck norris', '', 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 20:00:00', 89, 'chuck norris', '', 1);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 21:00:00', 0, 'chuck norris', '', 1);

INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 13:00:00', 300, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 14:00:00', 50, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 15:00:00', 482, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 16:00:00', 68, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 17:00:00', 174, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 18:00:00', 369, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 19:00:00', 42, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 20:00:00', 0, 'steven ceagal', '', 2);
INSERT INTO capteurUser (temps, pas, user, detection_alerte_user, id_telephone) VALUES ('2017-05-25 21:00:00', 0, 'steven ceagal', '', 2);