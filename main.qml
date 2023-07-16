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

    property string xas
    property string xas1
    property string qmlColor : "#272727"



    Connections {
        target: mapMouseActionController
        onPos_signal:{
            xas = mCoordinate.toString()

        }
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
                onCenterChanged: mapMouseActionController.currentRec(map1.visibleRegion.boundingGeoRectangle())

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
                                  mapMouseActionController.toCPPposClickedD(map1.toCoordinate(Qt.point(mouseX,mouseY)));
                            }
                              onPositionChanged :{
                                    mapMouseActionController.toCPPpos(map1.toCoordinate(Qt.point(mouseX,mouseY)));
                              }

                          }

                Rectangle{
                   id : topback
                   height : 60
                   width : parent.width - 60
                   color: "black"
                   opacity: 0.8
                   radius:5
                   z:5
                }

                Image {
                   id:atlas
                   source: "qrc:/icons/atlas.png"
                   height :74
                   antialiasing: true
                   smooth: true
                   z:5
               }

                RoundButton{
                  id:utilities
                  icon.source:"qrc:/icons/shape.png"
                  onClicked: utilityMenu.popup();
                  anchors.right: colour.left
                  anchors.rightMargin: 10
                  width:40
                  y:10
                  height: 40
                  radius:5
                  palette.buttonText: "white"
                  palette.button: qmlColor
                  z:5
               }

                RoundButton{
                  id:grid
                  icon.source:"qrc:/icons/grid.png"
                  onClicked: actionController.startDrawOptiontoAC(6) + mapMouseActionController.currentRec(map1.visibleRegion.boundingGeoRectangle())
                  anchors.right: choose.left
                  anchors.rightMargin: 10
                  width:40
                  y:10
                  height: 40
                  radius:5
                  palette.buttonText: "white"
                  palette.button: qmlColor
                  z:5
               }

                Menu{
                   id: utilityMenu
                   topMargin: 60
                   rightMargin: 115
                   width:50
                   z:5

                   MenuItem {
                       height:50
                       width:50
                       contentItem:  Image{
                       source: "qrc:/icons/line.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.startDrawOptiontoAC(1);
                       z:5

                   }
                   MenuItem {
                       height:50
                       width:50
                       contentItem:  Image{
                           source: "qrc:/icons/circle.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.startDrawOptiontoAC(2);
                       z:5
                   }
                   MenuItem {
                       height:50
                       width:50
                       contentItem: Image{
                                    source: "qrc:/icons/path.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.startDrawOptiontoAC(3);
                       z:5
                   }


               }

                RoundButton{
                  id:move
                  anchors.right: utilities.left
                  anchors.rightMargin: 10
                  radius:5
                  y:10
                  icon.source: "qrc:/icons/move.png"
                  height: 40
                  width:40
                  onClicked:actionController.startDrawOptiontoAC(4)
                  palette.buttonText: "white"
                  palette.button: qmlColor
                  z:5
               }

                RoundButton{
                  id:choose
                  anchors.right: move.left
                  anchors.rightMargin: 10
                  radius:5
                  y:10
                  icon.source: "qrc:/icons/choose.png"
                  height: 40
                  width:40
                  onClicked:actionController.startDrawOptiontoAC(5)
                  palette.buttonText: "white"
                  palette.button: qmlColor
                  z:5
               }

                RoundButton{
                   id:colour
                   anchors.right: topback.right
                   anchors.rightMargin: 10
                   radius:5
                   y:10
                   icon.source: "qrc:/icons/color.png"
                   height: 40
                   width:40
                   onClicked:colorMenu.popup()
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                Menu {
                   id: colorMenu
                   topMargin: 60
                   rightMargin: 65
                   width:45
                   z:5
                   MenuItem {

                        Rectangle{color: "crimson";height: 45 ;width:45}
                       onClicked: actionController.colorPicker("crimson")
                   }
                   MenuItem {
                       Rectangle{color: "purple";height: 45 ;width:45}
                       onClicked: actionController.colorPicker("purple")
                   }
                   MenuItem {
                       Rectangle{color: "deeppink";height: 45 ;width:45}
                       onClicked: actionController.colorPicker("deeppink")
                   }
                   MenuItem {
                       Rectangle{color: "orangered";height: 45 ;width:45}
                       onClicked: actionController.colorPicker("orangered")
                   }
                   MenuItem {
                        Rectangle{color: "yellowgreen";height: 45 ;width:45}
                       onClicked: actionController.colorPicker("yellowgreen")
                   }
                   MenuItem {
                       Rectangle{color: "deepskyblue";height: 45 ;width:45}
                       onClicked: actionController.colorPicker("deepskyblue")
                   }
                   MenuItem {
                       Rectangle{color: "white";height: 45 ;width:45}
                       onClicked: actionController.colorPicker("white")
                   }
                 }

                Rectangle{
                   id: konum
                   anchors.right: parent.right
                   anchors.bottom: parent.bottom
                   height:35
                   width:275
                   color: "black"
                   opacity: 0.8
                   radius:3
                   z:5

                 }

                Text {
                    id: konumText
                    text: xas
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height:30
                    width:260
                    color : "white"
                    font.pixelSize: 16
                    z:5

                }

                Rectangle{
                   id: zoom
                   anchors.right: parent.right
                   anchors.top: topback.bottom
                   anchors.topMargin: 10
                   height:410
                   width:60
                   color: "black"
                   opacity: 0.8
                   radius: 5
                   z:5

                 }

                RoundButton{
                   id:zooma
                   anchors.right: zoom.right
                   anchors.rightMargin: 10
                   anchors.top: zoom.top
                   anchors.topMargin: 10
                   icon.source:"qrc:/icons/zoomi.png"
                   radius:5
                   height: 40
                   width:40
                   onClicked:actionController.zoom(map1.zoomLevel+(1))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                RoundButton{
                   id:zomme
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: zooma.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/zoomo.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked:actionController.zoom(map1.zoomLevel-(1))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }



                RoundButton{
                   id:brge
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: zomme.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/tltl.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked:actionController.bearing(map1.bearing+(10))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                RoundButton{
                   id:brga
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: brge.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/tltr.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked:actionController.bearing(map1.bearing-(10))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                RoundButton{
                   id:tlte
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: brga.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/tilt2.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked:actionController.tilt(map1.tilt-(10))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                RoundButton{
                   id:tlta
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: tlte.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/tilt1.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked:actionController.tilt(map1.tilt+(10))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                RoundButton{
                   id:setCenter
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: tlta.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/setcenter.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked:actionController.startDrawOptiontoAC(7)
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                RoundButton{
                   id:gotocenter
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: setCenter.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/goto.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked: mapMouseActionController.gocntr()
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                }

                MapItemView {
                    model: lineModel
                    delegate:
                        MapPolyline{
                            id:xs
                            line.width: 5
                            line.color: clr
                            opacity: oppacity
                            z:3
                            path: [
                                    { latitude: latitude1, longitude: longitude1 },
                                    { latitude: latitude2, longitude: longitude2 }]

                            MouseArea {
                             hoverEnabled: true
                             anchors.fill: parent
                             acceptedButtons:  Qt.RightButton | Qt.MidButton
                             onClicked: {
                                 if (mouse.button === Qt.MidButton){
                                     popup.open()
                                 }
                                 else if (mouse.button === Qt.RightButton){
                                     actionController.highlight(Id)
                                 }
                             }
                            Popup {
                                 id: popup
                                 x: +50
                                 y: +50
                                 width: 175
                                 height: 100
                                 background: Rectangle {
                                         color: "black"
                                         border.color:qmlColor
                                         border.width: 3
                                     }
                                 opacity: 0.8
                                 closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                 contentItem: Text {
                                 text: "Id: " + Id +"\nFirst Coordinate: \n" + QtPositioning.coordinate(latitude1, longitude1)
                                     + "\nSecond Coordinate: \n" + QtPositioning.coordinate(latitude2, longitude2) + "\nDistance: " + dstnc + " m"
                                 color:"white"

                                 }
                            }
                           }

                       }



                }

                MapItemView {
                    model: pathModel

                    delegate:

                        MapPolyline{
                            id:pthr
                            line.width: 5
                            line.color: clr
                            opacity: oppacity
                            path: pth
                            MouseArea {
                             hoverEnabled: true
                             anchors.fill: parent
                             acceptedButtons:  Qt.RightButton| Qt.MidButton
                             onClicked: {
                                 if (mouse.button === Qt.MidButton){
                                     popuppth.open()
                                 }
                                 else if (mouse.button === Qt.RightButton){
                                     actionController.highlight(Id)
                                 }
                             }
                            Popup {
                                 id: popuppth
                                 x: +50
                                 y: +50
                                 width: 175
                                 height: 100
                                 background: Rectangle {
                                         color: "black"
                                         border.color:qmlColor
                                         border.width: 3

                                     }

                                 opacity: 0.8
                                 closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                 contentItem: Text {
                                 text: "Id: " + Id
                                 color: "white"

                                 }
                             }
                            }

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
                            MouseArea {
                             hoverEnabled: true
                             anchors.fill: parent
                             acceptedButtons:  Qt.RightButton| Qt.MidButton
                             onClicked: {
                                 if (mouse.button === Qt.MidButton){
                                     popupcrc.open()
                                 }
                                 else if (mouse.button === Qt.RightButton){
                                     actionController.highlight(Id)
                                 }
                             }
                            Popup {
                                 id: popupcrc
                                 x: 150
                                 y: 150
                                 width: 175
                                 height: 100
                                 background: Rectangle {
                                         color: "black"
                                         border.color:qmlColor
                                         border.width: 3

                                     }

                                 opacity: 0.8
                                 closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                 contentItem: Text {
                                 text: "Id: " + Id +"\nCenter Coordinate: \n" + QtPositioning.coordinate(latitude, longitude)
                                     + "\nRadius: " + rds + "\nArea: " + circleArea + " m^2"
                                 color:"white"

                                 }
                             }
                            }

                        }



                }

                MapItemView {
                    model: rectangleModel
                    delegate:
                        MapRectangle{
                            id:rec
                            color:"lightblue"
                            opacity: 0.3
                            border.width:0
                            topLeft: QtPositioning.coordinate(latitude1, longitude1)
                            bottomRight: QtPositioning.coordinate(latitude2, longitude2)


                        }



                }

                MapItemView {
                    model: gridModel
                    delegate:
                        MapPolyline{
                            id:gridd
                            line.width: 1
                            line.color: "white"
                            opacity: 0.5
                            z:3
                            path: [
                                    { latitude: latitude1, longitude: longitude1 },
                                    { latitude: latitude2, longitude: longitude2 }]
                    }
                }

            }

            Rectangle{
                x:500
                y:500
                height:500
                width:500
            }
}
