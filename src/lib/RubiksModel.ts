import * as THREE from 'three';
import gsap from 'gsap';

export default class RubiksModel {

    private _cube: THREE.Group;
    private _cubies: THREE.Object3D[];
    private _axis: THREE.Vector3;

    constructor(model: THREE.Group) {
        this._cube = model;
        this._cubies = model.children;
        this._axis = new THREE.Vector3(0, 0, 0);
        console.log("hello", this._cube)
    }

    public front(clockwise = true) {
        console.log("front");

        const layerZ = 0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.z - layerZ) < 0.1);
        this._axis.set(0, 0, 1);
        this._rotateLayer(cubies, clockwise);
    }

    public back(clockwise = true) {
        console.log("back");

        const layerZ = -0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.z - layerZ) < 0.1);
        this._axis.set(0, 0, 1);
        this._rotateLayer(cubies, clockwise);
    }

    public up(clockwise = true) {
        console.log("up");

        const layerY = 0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.y - layerY) < 0.1);
        this._axis.set(0, 1, 0);
        this._rotateLayer(cubies, clockwise);
    }

    public down(clockwise = true) {
        console.log("down");

        const layerY = -0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.y - layerY) < 0.1);
        this._axis.set(0, 1, 0);
        this._rotateLayer(cubies, clockwise);
    }

    public right(clockwise = true) {
        console.log("right");

        const layerX = 0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.x - layerX) < 0.1);
        this._axis.set(1, 0, 0);
        this._rotateLayer(cubies, clockwise);
    }

    public left(clockwise = true) {
        console.log("left");

        const layerX = -0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.x - layerX) < 0.1);
        this._axis.set(1, 0, 0);
        this._rotateLayer(cubies, clockwise);
    }

    private _rotateLayer(cubies: THREE.Object3D[], clockwise: boolean) {
        const group = new THREE.Group();
        this._cube.add(group);

        cubies.forEach(c => group.attach(c));

        const angle = (clockwise ? -1 : 1) * Math.PI * 0.5;

        gsap.to(group.rotation, {
            x: this._axis.x * angle,
            y: this._axis.y * angle,
            z: this._axis.z * angle,
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