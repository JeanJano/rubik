import * as THREE from 'three';
import gsap from 'gsap';

export default class RubiksModel {

    private _cube: THREE.Group;
    private _cubies: THREE.Object3D[];

    constructor(model: THREE.Group) {
        this._cube = model;
        this._cubies = model.children;
        console.log("hello", this._cube)
    }

    public front() {
        console.log("front");
    }

    public up(clockwise = true) {
        console.log("up");

        const layerY = 0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.y - layerY) < 0.1);

        this._rotateLayer(cubies, new THREE.Vector3(0, 1, 0), clockwise);
    }

    private _rotateLayer(cubies: THREE.Object3D[], axis: THREE.Vector3, clockwise: boolean) {
        const group = new THREE.Group();
        this._cube.add(group);

        cubies.forEach(c => group.attach(c));

        const angle = (clockwise ? -1 : 1) * Math.PI * 0.5;

        gsap.to(group.rotation, {
            x: axis.x * angle,
            y: axis.y * angle,
            z: axis.z * angle,
            duration: 0.5,
            onComplete: () => {
                console.log("complete")
                // Réattache les cubies au cube principal après rotation
                cubies.forEach(c => this._cube.attach(c));
                this._cube.remove(group);
                group.rotation.set(0, 0, 0);
            }
        });
    }

}