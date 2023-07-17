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
                   onClicked:actionController.zoom(map1.zoomLevel-(1))
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
                            opacity: 0.1
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
                    model: customEntityModel
                    delegate:
                        MapQuickItem{                      
                        id:entityGraph
                            sourceItem: Image {
                                id: transImage
                                width: 10* map1.zoomLevel
                                height: 10*map1.zoomLevel
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
                                            //popup.open()
                                            //transImage.source = ("qrc:/icons/mavi.png")

                                        }

                                    }
                              }


                            }
                        z:10

                     coordinate: QtPositioning.coordinate(latitude, longitude)


            }



}
            }
}
