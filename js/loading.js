/**
 * \file loading.js
 * \brief Charge le module listCapteur et le module historique dans la page index du dossier dashboard
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

ajaxRequest('GET','php/request.php/module/Capteur/listCapteur', loadHtmlAndJs);
ajaxRequest('GET','php/request.php/module/Capteur/historique', loadHtmlAndJs);