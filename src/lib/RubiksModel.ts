import * as THREE from 'three';
import gsap from 'gsap';

export default class RubiksModel {

    private _cube: THREE.Group;
    private _cubies: THREE.Object3D[];
    private _axis: THREE.Vector3;
    private _mix: string[];

    constructor(model: THREE.Group) {
        this._cube = model;
        this._cubies = model.children;
        this._axis = new THREE.Vector3(0, 0, 0);
        this._mix = [];
    }

    public front(clockwise = true): void {
        console.log("front");
        this._pushToMix("F", clockwise);

        const layerZ = 0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.z - layerZ) < 0.1);
        this._axis.set(0, 0, 1);
        this._rotateLayer(cubies, clockwise);
    }

    public back(clockwise = true): void {
        console.log("back");
        this._pushToMix("B", clockwise);

        const layerZ = -0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.z - layerZ) < 0.1);
        this._axis.set(0, 0, 1);
        this._rotateLayer(cubies, clockwise);
    }

    public up(clockwise = true): void {
        console.log("up");
        this._pushToMix("U", clockwise);

        const layerY = 0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.y - layerY) < 0.1);
        this._axis.set(0, 1, 0);
        this._rotateLayer(cubies, clockwise);
    }

    public down(clockwise = true): void {
        console.log("down");
        this._pushToMix("D", clockwise);

        const layerY = -0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.y - layerY) < 0.1);
        this._axis.set(0, 1, 0);
        this._rotateLayer(cubies, clockwise);
    }

    public right(clockwise = true): void {
        console.log("right");
        this._pushToMix("R", clockwise);

        const layerX = 0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.x - layerX) < 0.1);
        this._axis.set(1, 0, 0);
        this._rotateLayer(cubies, clockwise);
    }

    public left(clockwise = true): void {
        console.log("left");
        this._pushToMix("L", clockwise);

        const layerX = -0.3;
        const cubies = this._cubies.filter(c => Math.abs(c.position.x - layerX) < 0.1);
        this._axis.set(1, 0, 0);
        this._rotateLayer(cubies, clockwise);
    }

    private _pushToMix(operation: string, clockwise: boolean): void {
        if (!clockwise) {
            operation += "'";
        }
        if (operation == this._mix[this._mix.length - 1]) {
            if (clockwise)
                this._mix[this._mix.length - 1] += "2";
            else
                this._mix[this._mix.length - 1] = operation[0] + "2'";
        }
        else
            this._mix.push(operation);
    }

    private _rotateLayer(cubies: THREE.Object3D[], clockwise: boolean): void {
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
                cubies.forEach(c => this._cube.attach(c));
                this._cube.remove(group);
                group.rotation.set(0, 0, 0);
            }
        });
    }

    public getMix(): string[] { return this._mix; }

}