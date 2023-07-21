import QtQuick 2.15
import QtQuick3D 1.15

Node {
    id: rootNode

    DirectionalLight {
        id: sun
        x: 30.1112
        y: 19.9818
        z: 12.4784
        eulerRotation.x: -61.9009
        eulerRotation.y: 1.06969
        eulerRotation.z: -48.1693
        color: "#ffffffff"
    }


    Model {
        id: cube
        eulerRotation.x: -90
        source: "meshes/plane.mesh"

        DefaultMaterial {
            id: eYES_material
            diffuseColor: "#ffcccccc"
        }

        DefaultMaterial {
            id: game_dragon_material
            diffuseColor: "#ff1f0b04"
        }

        DefaultMaterial {
            id: game_dragon_001_material
            diffuseColor: "#ff2a2a2a"
        }
        materials: [
            eYES_material,
            game_dragon_material,
            game_dragon_001_material
        ]
    }


}
