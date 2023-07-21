import QtQuick 2.15
import QtQuick3D 1.15

Node {
    id: rootNode

    Model {
        id: plane
        y: 0.156927
        z: -1.69937
        eulerRotation.x: 7.1891
        source: "meshes/plane.mesh"

        DefaultMaterial {
            id: teker_demir_material
            diffuseColor: "#ffcccccc"
        }

        DefaultMaterial {
            id: motor_ic_material
            diffuseColor: "#ff000000"
        }
        materials: [
            teker_demir_material,
            teker_demir_material,
            teker_demir_material,
            teker_demir_material,
            teker_demir_material,
            teker_demir_material,
            motor_ic_material,
            teker_demir_material
        ]
    }

    DirectionalLight {
        id: sun
        x: 3.92652
        y: 2.19184
        z: 8.00159
        eulerRotation.x: -37.2753
        eulerRotation.y: 35.7756
        eulerRotation.z: 2.84471e-06
    }

    PerspectiveCamera {
        id: camera
        x: 10.8038
        y: 1.98764
        z: 7.88157
        eulerRotation.x: -8.82349
        eulerRotation.y: 57.3531
        eulerRotation.z: -1.42438e-05
        clipNear: 0.1
        clipFar: 100
        fieldOfView: 49.1343
        fieldOfViewOrientation: Camera.Horizontal
    }
}
