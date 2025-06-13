import * as THREE from 'three';
import gsap from 'gsap';

interface CubeAction {
    move: string;
    clockwise: boolean;
}

export default class RubiksModel {

    private _cube: THREE.Group;
    private _cubies: THREE.Object3D[];
    private _axis: THREE.Vector3;
    private _mix: string[];
    private _speed: number;
    private _queue: CubeAction[];
    private _isAnimated: boolean;

    constructor(model: THREE.Group) {
        this._cube = model;
        this._cubies = model.children;
        this._axis = new THREE.Vector3(0, 0, 0);
        this._mix = [];
        this._speed = 400;
        this._queue = [];
        this._isAnimated = false;
    }

    public front(clockwise = true): void {
        this._queue.push({move: "F", clockwise: clockwise});
        this._processQueue();
    }

    public back(clockwise = true): void {
        this._queue.push({move: "B", clockwise: clockwise});
        this._processQueue();
    }

    public up(clockwise = true): void {
        this._queue.push({move: "U", clockwise: clockwise});
        this._processQueue();
    }

    public down(clockwise = true): void {
        this._queue.push({move: "D", clockwise: clockwise});
        this._processQueue();
    }

    public right(clockwise = true): void {
        this._queue.push({move: "R", clockwise: clockwise});
        this._processQueue();
    }

    public left(clockwise = true): void {
        this._queue.push({move: "L", clockwise: clockwise});
        this._processQueue();
    }

    public async shuffle(mix: string[]) {
        for (let i = 0; i < mix.length; i++) {
            console.log(mix[i])
            await this._execAction(mix[i]);
            await this._sleep(this._speed);
        }
    }

    public randomMix(): void {
        const movesArray = ["F", "D", "L", "R", "U", "B"];

        for (let i = 0; i < 30; i++) {
            const randomIndex = Math.floor(Math.random() * movesArray.length);
            let move = movesArray[randomIndex];
            const clockwise = Math.random() > 0.5;
            if (Math.random() < 0.3) move += "2"; // ajouter 2 de temps en temps

            this._queue.push({ move, clockwise });
        }

        this._processQueue();
    }

    public raycastMiddleCube(event: MouseEvent, camera: THREE.Camera, clockwise: boolean) : THREE.Object3D | null {
        const raycaster = new THREE.Raycaster()
        const mouse = new THREE.Vector2()

        mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
        mouse.y = -(event.clientY / window.innerHeight) * 2 + 1;

        raycaster.setFromCamera(mouse, camera)

        const intersects = raycaster.intersectObjects(this._cubies, true)

        if (intersects.length > 0) {
            if (intersects[0].object.name === "Cube016_2") {
                this.front(clockwise)
            } else if (intersects[0].object.name === "Cube023_2") {
                this.up(clockwise)
            } else if (intersects[0].object.name === "Cube018_2") {
                this.left(clockwise)
            } else if (intersects[0].object.name === "Cube004_2") {
                this.right(clockwise)
            } else if (intersects[0].object.name === "Cube027_2") {
                this.down(clockwise)
            } else if (intersects[0].object.name === "Cube025_2") {
                this.back(clockwise)
            }
        }

        return null
    }

    private async _processQueue(): Promise<void> {
        if (this._isAnimated || this._queue.length === 0)
            return;
        this._isAnimated = true;

        while (this._queue.length > 0) {
            const action = this._queue.shift()!;
            this._pushToMix(action.move, action.clockwise);
            await this._execAction(action.move, action.clockwise);
            const adjustedSpeed = Math.max(0.001, this._speed - this._queue.length * 50);
            console.log(adjustedSpeed)
            await this._sleep(adjustedSpeed);
        }

        this._isAnimated = false;
    }

    private async _sleep(ms: number): Promise<void> {
        return new Promise(
            resolve => setTimeout(resolve, ms)
        );
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
        else {
            this._mix.push(operation);
        }
    }

    private _rotateLayer(cubies: THREE.Object3D[], axis: THREE.Vector3, clockwise: boolean): void {
        const group = new THREE.Group();
        this._cube.add(group);

        cubies.forEach(c => group.attach(c));
        const angle = (clockwise ? -1 : 1) * Math.PI * 0.5;

        gsap.to(group.rotation, {
            x: axis.x * angle,
            y: axis.y * angle,
            z: axis.z * angle,
            duration: this._speed / 1000 - 0.05,
            onComplete: () => {
                cubies.forEach(c => this._cube.attach(c));
                this._cube.remove(group);
                group.rotation.set(0, 0, 0);
            }
        });

        this._displayAction();
    }

    private _displayAction(): void {
        const backgroud = document.getElementsByClassName("background");
        backgroud[0].innerHTML = this._mix.join(" ");
    }

    private async _execAction(action: string, clockwise = true) {
        const count = action.includes("2") ? 2 : 1;
        const base = action[0];
        const isPrime = action.includes("'");

        const direction = isPrime ? !clockwise : clockwise;

        for (let i = 0; i < count; i++) {
            switch (base) {
                case "F": this._rotate("F", direction); break;
                case "B": this._rotate("B", direction); break;
                case "L": this._rotate("L", direction); break;
                case "R": this._rotate("R", direction); break;
                case "U": this._rotate("U", direction); break;
                case "D": this._rotate("D", direction); break;
            }
            await this._sleep(this._speed);
        }
    }

    private _rotate(face: string, clockwise: boolean): void {
        const layerValue = 0.3;
        let axis = new THREE.Vector3();
        let cubies: THREE.Object3D[] = [];

        switch (face) {
            case "F":
                cubies = this._cubies.filter(c => Math.abs(c.position.z - layerValue) < 0.1);
                axis.set(0, 0, 1);
                break;
            case "B":
                cubies = this._cubies.filter(c => Math.abs(c.position.z + layerValue) < 0.1);
                axis.set(0, 0, 1);
                clockwise = !clockwise;
                break;
            case "U":
                cubies = this._cubies.filter(c => Math.abs(c.position.y - layerValue) < 0.1);
                axis.set(0, 1, 0);
                break;
            case "D":
                cubies = this._cubies.filter(c => Math.abs(c.position.y + layerValue) < 0.1);
                axis.set(0, 1, 0);
                clockwise = !clockwise;
                break;
            case "R":
                cubies = this._cubies.filter(c => Math.abs(c.position.x - layerValue) < 0.1);
                axis.set(1, 0, 0);
                break;
            case "L":
                cubies = this._cubies.filter(c => Math.abs(c.position.x + layerValue) < 0.1);
                axis.set(1, 0, 0);
                clockwise = !clockwise;
                break;
        }

        this._rotateLayer(cubies, axis, clockwise);
    }

    public getMix(): string[] { return this._mix; }

}