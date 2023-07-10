import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.12
import QtQuick.Controls 2.12
import QtPositioning 5.12
import QtQml 2.12


Window {
    id: window
    width: 1240
    height: 720
    visible: true
    title: qsTr("Project:ATLAS")







        Plugin{
            id: gsat
            name: "osm"
            PluginParameter { name: "osm.mapping.providersrepository.address"; value: Qt.resolvedUrl("./providers/satellite/") }
            PluginParameter { name: "osm.mapping.cache.directory"; value: "cache" }
            PluginParameter { name: "osm.mapping.cache.disk.size"; value: 0 }
        }

            Map{
                id: map1
                anchors.fill: parent
                plugin: gsat
                center: QtPositioning.coordinate(39.91, 35.75)
                zoomLevel: 8




                // TODO PNG...

            }

}
