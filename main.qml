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


    Connections {
        target: mapMouseActionController
     }
    Connections {
        target: mapController
     }
    Connections {
        target: actionController
     }
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
                center: mapController.center
                zoomLevel: mapController.zoomLevel
                tilt: mapController.tilt
                bearing: mapController.bearing

                MouseArea {
                            hoverEnabled : true
                            anchors.fill : parent
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            onClicked: {
                                if (mouse.button === Qt.RightButton)
                                    mapMouseActionController.toCPPposClickedR(map1.toCoordinate(Qt.point(mouseX,mouseY)));
                                else
                                    mapMouseActionController.toCPPposClickedL(map1.toCoordinate(Qt.point(mouseX,mouseY)));

                              }
                              onDoubleClicked: {
                                  actionController.toCPPposClickedD(map1.toCoordinate(Qt.point(mouseX,mouseY)));


                            }
                              onPositionChanged :{
                                    mapMouseActionController.toCPPpos(map1.toCoordinate(Qt.point(mouseX,mouseY)));
                              }
                          }


                Button{
                   id:linee
                   text: "Draw Line"
                   onClicked: actionController.startDrawOptiontoAC(1);

                }
                Button{

                   id:circle
                   y: linee.height
                   text: "Draw Circle"
                   onClicked: actionController.startDrawOptiontoAC(2);

                }


















                MapItemView {
                    model: lineModel
                    delegate:
                        MapPolyline{
                            id:xs
                            //color:clr
                            line.width: 5

                            line.color: clr
                            opacity: oppacity

                            path: [
                                    { latitude: latitude1, longitude: longitude1 },
                                    { latitude: latitude2, longitude: longitude2 }]
                            z:10

                        }



                }

                MapItemView {
                    model: pathModel
                    delegate:
                        MapPolyline{
                            line.width: 5
                            line.color: clr
                            opacity: oppacity
                            path: pth
                        }



                }

                MapItemView {
                    model: circleModel
                    delegate:
                        MapCircle{
                            id:crcl
                            color:clr
                            radius: rds
                            opacity: oppacity
                            center: QtPositioning.coordinate(latitude, longitude)

                        }



                }






                // TODO PNG...

            }

}
