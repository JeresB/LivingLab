/**
 * \file setGraph.js
 * \brief Permet la création de graphique
 * \author {Théo D. & Jeremy B.}
 * \version 1
 */

/**
 *  \brief setGraph
 *
 *  Permet la création de graphique
 *
 *  \param div : div où est charger le graphique
 *  \param name : nom du graphique
 *  \param nameSerie : nom de la série de données
 *  \param date : tableau de date correspondant aux valeurs des capteurs
 *  \param value : tableau de valeurs des capteurs
 *  \param seuil1 : Seuil 1 des données
 *  \param seuil2 : Seuil 2 des données
 */
function setGraph(div, name, nameSerie, date, value, seuil1, seuil2) {
    /// Ajout de la class thumbnail de bootstrap autour du graphique
    var graph = document.getElementById(div);
    graph.className = 'thumbnail';
    
    /// Création du graphique HIGHCHARTS
    Highcharts.chart(div, {
        chart: {
            type: 'spline'
        },
        title: {
            text: name
        },

        subtitle: {
            text: 'Source: LivingLab'
        },
        xAxis: {
            categories: date
        },
    
        yAxis: {
            title: {
                text: name
            },
            minorGridLineWidth: 0,
            gridLineWidth: 0,
            alternateGridColor: null,
            plotBands: [{
                from: 0,
                to: seuil1,
                color: 'white',
                label: {
                    text: '',
                    style: {
                        color: 'black'
                    }
                }
            }, {
                from: seuil1,
                to: seuil1 + 1,
                color: 'red',
                label: {
                    text: '',
                    style: {
                        color: 'white'
                    }
                }
            }, {
                from: seuil2,
                to: seuil2 + 1,
                color: 'red',
                label: {
                    text: '',
                    style: {
                        color: 'white'
                    }
                }
            }]
        },
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle'
        }, 
        series: [{
            name: nameSerie,
            data: value
        }]
    });  
}