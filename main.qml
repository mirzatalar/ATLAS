import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.5
import QtQuick.Controls 2.12
import QtPositioning 5.12
import QtQml 2.12
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15
import QtQuick3D.Helpers 1.15
import QtMultimedia 5.15
import "dragon"
//import "Airbus A310"


Window {
    id: window
    width: 1240
    height: 720
    visible: true
    title: qsTr("Project:ATLAS")
    visibility: "FullScreen"

    property string xas
    property string xas1
    property string qmlColor : "#0084ff"





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

            PluginParameter { name: "osm.mapping.cache.disk.size"; value: 9999999999 }
        }

            Map{
                Rectangle {
                    id:reca
                    visible: true
                      anchors.fill: parent
                      color:"black"
                      z:100

                      MediaPlayer {
                          id: mediaPlayer
                          source: "qrc:/video/intro.avi" // Video dosyasının yolunu buraya girin

                          autoLoad: true
                          autoPlay: true
                          onStopped: reca.visible = false

                      }

                      VideoOutput {
                          anchors.fill: parent
                          source: mediaPlayer


                      }
                  }

                id: map1
                anchors.fill: parent
                plugin: gsat
                center: mapController.center
                zoomLevel: mapController.zoomLevel
                tilt: mapController.tilt
                bearing: mapController.bearing
                onCenterChanged:{ mapMouseActionController.currentRec(map1.visibleRegion.boundingGeoRectangle())
                                   mapController.center = map1.center}
                onZoomLevelChanged: mapController.zoomLevel = map1.zoomLevel

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
                  z:53
                  ToolTip {
                        y:50
                        delay: 750
                        visible: utilities.hovered
                        contentItem: Text {
                        text: "Draw"

                        color:"white"}

                         background: Rectangle {
                                 color: "black"
                                 border.color:qmlColor
                                 border.width: 3
                                 opacity: 0.5
                             }
                     }
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
                  ToolTip {
                        y:50
                        delay: 750
                        visible: grid.hovered
                        contentItem: Text {
                        text: "Grid"

                        color:"white"}

                         background: Rectangle {
                                 color: "black"
                                 border.color:qmlColor
                                 border.width: 3
                                 opacity: 0.5
                             }
                     }
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
                  ToolTip {
                        y:50
                        delay: 750
                        visible: move.hovered
                        contentItem: Text {
                        text: "Move"

                        color:"white"}

                         background: Rectangle {
                                 color: "black"
                                 border.color:qmlColor
                                 border.width: 3
                                 opacity: 0.5
                             }
                     }



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
                  ToolTip {
                        y:50
                        delay: 750
                        visible: choose.hovered
                        contentItem: Text {
                        text: "Select"

                        color:"white"}

                         background: Rectangle {
                                 color: "black"
                                 border.color:qmlColor
                                 border.width: 3
                                 opacity: 0.5
                             }
                     }

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
                   ToolTip {
                         y:50
                         delay: 750
                         visible: colour.hovered
                         contentItem: Text {
                         text: "Change\nColor"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }

                RoundButton{
                   id:del
                   anchors.right: grid.left
                   anchors.rightMargin: 10
                   radius:5
                   y:10
                   icon.source: "qrc:/icons/delete.png"
                   height: 40
                   width:40
                   onClicked:actionController.startDrawOptiontoAC(8)
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         y:50
                         delay: 750
                         visible: del.hovered
                         contentItem: Text {
                         text: "Delete"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }

                RoundButton{
                   id:entity
                   anchors.right: del.left
                   anchors.rightMargin: 10
                   radius:5
                   y:10
                   icon.source: "qrc:/icons/entity.png"
                   height: 40
                   width:40
                   onClicked:entityMenu.popup()
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         y:50
                         delay: 750
                         visible: entity.hovered
                         contentItem: Text {
                         text: "Add Entity"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }

                RoundButton{
                   id:movemap
                   anchors.right: entity.left
                   anchors.rightMargin: 10
                   radius:5
                   y:10
                   icon.source: "qrc:/icons/movemap.png"
                   height: 40
                   width:40
                   onClicked:actionController.startDrawOptiontoAC(9)
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         y:50
                         delay: 750
                         visible: movemap.hovered
                         contentItem: Text {
                         text: "Move Map"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }

                RoundButton{
                   id:addloc
                   anchors.right: liste.left
                   anchors.rightMargin: 10
                   radius:5
                   y:10
                   icon.source: "qrc:/icons/addloc.png"
                   height: 40
                   width:40
                   onClicked:actionController.startDrawOptiontoAC(10)
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         y:50
                         delay: 750
                         visible: addloc.hovered
                         contentItem: Text {
                         text: "Add Loc"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }
















//                RoundButton{
//                   id:speed
//                   anchors.right: movemap.left
//                   anchors.rightMargin: 10
//                   radius:5
//                   y:10
//                   icon.source: "qrc:/icons/speed.png"
//                   height: 40
//                   width:40
//                   onClicked: slider.visible = !slider.visible
//                   palette.buttonText: "white"
//                   palette.button: qmlColor
//                   z:5
//                   ToolTip {
//                         y:50
//                         delay: 750
//                         visible: speed.hovered
//                         contentItem: Text {
//                         text: "Entities"

//                         color:"white"}

//                          background: Rectangle {
//                                  color: "black"
//                                  border.color:qmlColor
//                                  border.width: 3
//                                  opacity: 0.5
//                              }
//                      }
//                   Slider {
//                          id: slider
//                          y:55
//                          visible:false
//                          orientation: "Vertical"
//                          height: 100
//                          from: 1
//                          to: 70
//                          z:5
//                          onValueChanged: actionController.speed(value)
//                   }
//                   Rectangle{
//                        id:sliderback
//                        y:30
//                        visible:slider.visible
//                        height: 130
//                        width:40
//                        color:qmlColor
//                        opacity:0.8
//                   }
//                }

                Menu {
                   id: entityMenu
                   topMargin: 60
                   rightMargin: 367.5
                   width:45
                   z:5

                   MenuItem {
                       height:45
                       width:45
                       contentItem:  Image{
                       source: "qrc:/icons/icon_civil_car.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.addEntity(1);
                       z:5

                   }
                   MenuItem {
                       height:45
                       width:45
                       contentItem:  Image{
                       source: "qrc:/icons/icon_aircraft.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.addEntity(2);
                       z:5

                   }
                   MenuItem {
                       height:45
                       width:45
                       contentItem:  Image{
                       source: "qrc:/icons/icon_drone.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.addEntity(3);
                       z:5

                   }
                   MenuItem {
                       height:45
                       width:45
                       contentItem:  Image{
                       source: "qrc:/icons/icon_tank.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.addEntity(4);
                       z:5

                   }
                   MenuItem {
                       height:45
                       width:45
                       contentItem:  Image{
                       source: "qrc:/icons/icon_helicopter.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.addEntity(5);
                       z:5

                   }
                   MenuItem {
                       height:45
                       width:45
                       contentItem:  Image{
                       source: "qrc:/icons/icon_warship.png"}
                       background: Rectangle{color: "black"; opacity:0.8}
                       onClicked: actionController.addEntity(6);
                       z:5

                   }

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
                   height:460
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
                   onClicked:actionController.zoom(map1.zoomLevel+(0.3))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         x:-60
                         y:5
                         delay: 750
                         visible: zooma.hovered
                         contentItem: Text {
                         text: "Zoom In"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                   onClicked:actionController.zoom(map1.zoomLevel-(0.3))
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         x:-70
                         y:5
                         delay: 750
                         visible: zomme.hovered
                         contentItem: Text {
                         text: "Zoom Out"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                   ToolTip {
                         x:-70
                         y:5
                         delay: 750
                         visible: brge.hovered
                         contentItem: Text {
                         text: "Bearing+"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                   ToolTip {
                         x:-65
                         y:5
                         delay: 750
                         visible: brga.hovered
                         contentItem: Text {
                         text: "Bearing-"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                   ToolTip {
                         x:-45
                         y:5
                         delay: 750
                         visible: tlte.hovered
                         contentItem: Text {
                         text: "Tilt-"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                   ToolTip {
                         x:-45
                         y:5
                         delay: 750
                         visible: tlta.hovered
                         contentItem: Text {
                         text: "Tilt+"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                   ToolTip {
                         x:-75
                         y:5
                         delay: 750
                         visible: setCenter.hovered
                         contentItem: Text {
                         text: "Set Center"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                   ToolTip {
                         x:-85
                         y:5
                         delay: 750
                         visible: gotocenter.hovered
                         contentItem: Text {
                         text: "Go to Center"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }

                RoundButton{
                   id:reset
                   anchors.left: zoom.left
                   anchors.leftMargin: 10
                   anchors.top: gotocenter.bottom
                   anchors.topMargin: 10
                   icon.source: "qrc:/icons/reset.png"
                   height: 40
                   width:40
                   radius:5
                   onClicked:actionController.startDrawOptiontoAC(11)
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         x:-70
                         y:5
                         delay: 750
                         visible: zomme.hovered
                         contentItem: Text {
                         text: "Zoom Out"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
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
                            color:"#008BFF"
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

                MapItemView {
                    model: locationModel
                    delegate:
                        MapQuickItem{
                        id:loca

                            sourceItem: Image {
                                id: loc
                                width: 5* map1.zoomLevel
                                height: 5*map1.zoomLevel
                                source: icon
                                MouseArea {
                                    hoverEnabled: true

                                    anchors.fill: parent
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                                    onClicked: {
                                        if (mouse.button === Qt.RightButton){

                                           actionController.deleteLoc(Id)

                                        }
                                        else if (mouse.button === Qt.LeftButton){
                                         loccoor.open()

                                        }

                                    }

                                    Popup {
                                        id: loccoor
                                        x:+50
                                        y:+50
                                        background: Rectangle {
                                                color: "black"
                                                border.color:qmlColor
                                                border.width: 2

                                            }

                                        opacity: 0.6

                                        width: 160
                                        height: 30

                                        closePolicy: Popup.CloseOnPressOutside
                                         contentItem: Text { text: "" + QtPositioning.coordinate(latitude, longitude)
                                             color:"white"

                                         }
                                    }
                                }
                        }
                        z:10

                         coordinate: QtPositioning.coordinate(latitude, longitude)




                }

                }


                Popup {
                    id: popupcoor
                     anchors.centerIn: Overlay.overlay

                    topMargin: 10*map1.height / 100
                    leftMargin: 68*map1.width / 100
                    background: Rectangle {
                            color: "black"
                            border.color:qmlColor
                            border.width: 5

                        }

                    opacity: 0.8

                    width: map1.width / 4
                    height: 83* map1.height / 100

                    closePolicy: Popup.CloseOnPressOutside

                    Component {
                        id: contactDelegate1
                        Item {
                            width: popupcoor.width; height: popupcoor.height/8;
                            Row{
                             spacing: 10

                            Image {
                                //y:50
                                id:asd
                                height: popupcoor.width / 8
                                width: popupcoor.width / 8
                                opacity: 1
                                source: icon}

                            Column {

                                Text { font.pixelSize: (3* popupcoor.width / 4) * 0.042;text: '<b>Id:</b> ' + Id ;color:"white" }
                                Text {font.pixelSize: (3* popupcoor.width / 4) * 0.042;text:"<b>Coordinate:</b> \n" + QtPositioning.coordinate(latitude, longitude)
                                color:"white"}


                            }



                            RoundButton{


                                radius:5
                                onClicked:  mapMouseActionController.cntr(QtPositioning.coordinate(latitude, longitude))
                                icon.source: "qrc:/icons/info.png"
                                icon.height: popupcoor.width / 9 - 10
                                icon.width: popupcoor.width / 9 - 10
                                height: popupcoor.width / 9
                                width: popupcoor.width / 9
                                 palette.buttonText: "white"
                                 palette.button: "#008BFF"
                            }

                            }

                        }


                    }

                    ListView {
                        anchors.fill: parent
                        model: locationModel
                        delegate: contactDelegate1

                        focus: true

                    }
                }






                RoundButton{
                   id:coors
                   anchors.right: addloc.left
                   anchors.rightMargin: 10
                   radius:5
                   y:10
                   icon.source: "qrc:/icons/locmenu.png"
                   height: 40
                   width:40
                   onClicked: popupcoor.open()
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         y:50
                         delay: 750
                         visible: coors.hovered
                         contentItem: Text {
                         text: "Locations"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }


























                RoundButton{
                   id:liste
                   anchors.right: movemap.left
                   anchors.rightMargin: 10
                   radius:5
                   y:10
                   icon.source: "qrc:/icons/list.png"
                   height: 40
                   width:40
                   onClicked: popupx.open()
                   palette.buttonText: "white"
                   palette.button: qmlColor
                   z:5
                   ToolTip {
                         y:50
                         delay: 750
                         visible: liste.hovered
                         contentItem: Text {
                         text: "Entities"

                         color:"white"}

                          background: Rectangle {
                                  color: "black"
                                  border.color:qmlColor
                                  border.width: 3
                                  opacity: 0.5
                              }
                      }
                }


                Popup {
                    id: popupx
                     anchors.centerIn: Overlay.overlay

                    topMargin: 10*map1.height / 100
                    leftMargin: 68*map1.width / 100
                    background: Rectangle {
                            color: "black"
                            border.color:qmlColor
                            border.width: 5

                        }

                    opacity: 0.8

                    width: map1.width / 4
                    height: 83* map1.height / 100

                    closePolicy: Popup.CloseOnPressOutside

                    Component {
                        id: contactDelegate
                        Item {
                            width: popupx.width; height: popupx.height/8;
                            Row{
                             spacing: 10
                            Column {

                                Text { font.pixelSize: (3* popupx.width / 4) * 0.042;text: '<b>Id:</b> ' + Id ;color:"white" }
                                Text {font.pixelSize: (3* popupx.width / 4) * 0.042;text:'<b>\nType Name:</b> ' + typename ;color:"white"}
                                Text {font.pixelSize: (3* popupx.width / 4) * 0.042;text:"<b>Coordinate:</b> \n" + QtPositioning.coordinate(latitude, longitude)
                                color:"white"}


                            }

                            Image {


                                //y:50
                                id:asd
                                height: popupx.width / 8
                                width: popupx.width / 8
                                opacity: 1

                                source: icon}


                            RoundButton{


                                radius:5
                                onClicked:  popupa.open()
                                icon.source: "qrc:/icons/info.png"
                                icon.height: popupx.width / 9 - 10
                                icon.width: popupx.width / 9 - 10
                                height: popupx.width / 9
                                width: popupx.width / 9
                                 palette.buttonText: "white"
                                 palette.button: "#008BFF"
                            }

                            }
                            Popup {
                                id: popupa
                                 anchors.centerIn: Overlay.overlay

                                topMargin: 11*map1.height / 100
                                rightMargin: 73.5*map1.width / 100
                                background: Rectangle {
                                        color: "black"
                                        border.color:qmlColor
                                        border.width: 5

                                    }

                                opacity: 0.8

                                width: map1.width / 4
                                height: 87* map1.height / 100

                                closePolicy: Popup.CloseOnEscape

                                contentItem: Text {
                                    topPadding: thereed.height + 100
                                    id:infos
                                    text: "Id: " + Id +"\nCenter Coordinate: \n" + QtPositioning.coordinate(latitude, longitude)
                                        + "\nHeading: " + (-heading) + "\nSpeed: " + Speed
                                    font.pointSize: 12
                                    color:"white"
                                }

                                View3D {
                                   height: 92.5*popupa.width/100

                                   id: thereed
                                   anchors.top: title.bottom
                                   anchors.left: popupa.left
                                   anchors.right: popupa.right
                                   anchors.leftMargin: 10
                                   anchors.rightMargin: 10
                                   width:92.5*popupa.width/100
                                   //anchors.fill: parent
                                   environment: SceneEnvironment {
                                     clearColor: "#000000"
                                     backgroundMode: SceneEnvironment.Color
                                   }
                                   Node {
                                     id: scene
                                     PerspectiveCamera {
                                       id: camera
                                       z: 100

                                       PropertyAnimation on z {
                                       //loops: Animation.Infinite
                                         duration: 3000
                                         to: 600
                                         from: 1000
                                       }
                                       PropertyAnimation on y {
                                       loops: Animation.Infinite
                                         duration: 20000
                                         to: 0
                                         from: 300
                                       }
                                     }

                                     DirectionalLight {
                                       z: -400
                                       x:400
                                       y:500
                                       brightness: 400
                                       color:"#272727"
                                     }



                                     Dragon{
                                           id:eci
                                           xm : reelicon


                                            PropertyAnimation on eulerRotation.y {
                                              loops: Animation.Infinite
                                              duration: 5000
                                              to: 360
                                              from: 0
                                            }
                                     }


                                   }
                                 }
                                Text {

                                    id:title
                                    text: typename
                                    font.pointSize: 24
                                    leftPadding: popupa.width/2 - contentWidth/2 - 15
                                    color: "white"
                                }

                               RoundButton{
                                    x: popupa.width / 50
                                    y: 38*popupa.height / 50
                                    id:gotoitem
                                    radius:5

                                    icon.source: "qrc:/icons/goto.png"
                                    icon.height: 50
                                    icon.width: 50
                                    height: 60
                                    width:60
                                    onClicked:mapMouseActionController.cntr(QtPositioning.coordinate(latitude, longitude))


                                    palette.buttonText: "white"
                                    palette.button: qmlColor
                                    z:5
                                }

                               RoundButton{
                                    x: popupa.width - 30
                                    y:-20

                                    id:closepp
                                    radius:5

                                    icon.source: "qrc:/icons/close.png"
                                    icon.height: 20
                                    icon.width: 20
                                    height: 25
                                    width:25
                                    onClicked:popupa.close()

                                    palette.buttonText: "white"
                                    palette.button: "red"
                                    z:5
                                }
                                   // background: Rectangle{color: "black"; opacity:0.8}
                            }
                        }


                    }

                    ListView {
                        anchors.fill: parent
                        model: customEntityModel
                        delegate: contactDelegate

                        focus: true

                    }
                }


                MapItemView {
                    model: customEntityModel
                    delegate:
                        MapQuickItem{                      
                        id:entityGraph

                            sourceItem: Image {
                                id: transImage
                                width: 5* map1.zoomLevel
                                height: 5*map1.zoomLevel
                                source: icon
                                rotation:heading


                                MouseArea {
                                    hoverEnabled: true

                                    anchors.fill: parent
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                                    onClicked: {
                                        if (mouse.button === Qt.RightButton){

                                           actionController.highlightEntity(Id)

                                        }
                                        else if (mouse.button === Qt.LeftButton){
                                         test.open() + popupa.open()

                                        }

                                    }

                                    Popup {
                                    id:test

                                    background: Rectangle {

                                           height:transImage.height
                                           width: transImage.width
                                           color: "white"
                                           border.color:qmlColor
                                           border.width: 1
                                           opacity: 0.3

                                       }
                                   //opacity: 1

                                    }

                                    Popup {
                                        id: popupa
                                         anchors.centerIn: Overlay.overlay

                                        topMargin: 11*map1.height / 100
                                        rightMargin: 73.5*map1.width / 100
                                        background: Rectangle {
                                                color: "black"
                                                border.color:qmlColor
                                                border.width: 5

                                            }

                                        opacity: 0.8

                                        width: map1.width / 4
                                        height: 87* map1.height / 100

                                        closePolicy: Popup.CloseOnEscape

                                        contentItem: Text {
                                            topPadding: 100 + view.height
                                            id:infos
                                            text: "Id: " + Id +"\nCenter Coordinate: \n" + QtPositioning.coordinate(latitude, longitude)
                                                + "\nHeading: " + (-heading) + "\nSpeed: " + Speed
                                            font.pointSize: 12
                                            color:"white"

                                        }


                                        View3D {
                                           height: 92.5*popupa.width/100

                                           id: view
                                           anchors.top: title.bottom
                                           anchors.left: popupa.left
                                           anchors.right: popupa.right
                                           anchors.leftMargin: 10
                                           anchors.rightMargin: 10
                                           width:92.5*popupa.width/100
                                           //anchors.fill: parent
                                           environment: SceneEnvironment {
                                             clearColor: "#000000"
                                             backgroundMode: SceneEnvironment.Color
                                           }
                                           Node {
                                             id: scene
                                             PerspectiveCamera {
                                               id: camera
                                               z: 100

                                               PropertyAnimation on z {
                                               //loops: Animation.Infinite
                                                 duration: 3000
                                                 to: 600
                                                 from: 1000
                                               }
                                               PropertyAnimation on y {
                                               loops: Animation.Infinite
                                                 duration: 20000
                                                 to: 0
                                                 from: 300
                                               }
                                             }
                                             DirectionalLight {
                                               z: 400
                                               brightness: 600
                                               color:"#272727"
                                             }


                                             Dragon{
                                                   id:eci
                                                   xm : reelicon


                                                    PropertyAnimation on eulerRotation.y {
                                                      loops: Animation.Infinite
                                                      duration: 5000
                                                      to: 360
                                                      from: 0
                                                    }
                                             }


                                           }
                                         }

                                        Text {

                                            id:title
                                            text: typename
                                            font.pointSize: 24
                                            leftPadding: popupa.width/2 - contentWidth/2 - 15
                                            color: "white"
                                        }

                                       RoundButton{
                                            x: popupa.width / 50
                                            y: 38*popupa.height / 50
                                            id:gotoitem
                                            radius:5

                                            icon.source: "qrc:/icons/goto.png"
                                            icon.height: 50
                                            icon.width: 50
                                            height: 60
                                            width:60
                                            onClicked:mapMouseActionController.cntr(entityGraph.coordinate)


                                            palette.buttonText: "white"
                                            palette.button: qmlColor
                                            z:5
                                        }

                                       RoundButton{
                                            x: popupa.width - 30
                                            y:-20

                                            id:closepp
                                            radius:5

                                            icon.source: "qrc:/icons/close.png"
                                            icon.height: 20
                                            icon.width: 20
                                            height: 25
                                            width:25
                                            onClicked:popupa.close() + test.close()

                                            palette.buttonText: "white"
                                            palette.button: "red"
                                            z:5
                                        }
                                           // background: Rectangle{color: "black"; opacity:0.8}
                                    }
                              }


                            }
                        z:10

                     coordinate: QtPositioning.coordinate(latitude, longitude)



            }



}


            }
}
