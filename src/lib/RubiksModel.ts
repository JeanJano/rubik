import * as THREE from 'three';
import gsap from 'gsap';
import type { CubeAction } from './CubeAction';

export default class RubiksModel {

    private _cube: THREE.Group;
    private _cubies: THREE.Object3D[];
    private _mix: CubeAction[];
    private _speed: number;
    private _queue: CubeAction[];
    private _isAnimated: boolean;

    constructor(model: THREE.Group) {
        this._cube = model;
        this._cubies = model.children;
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

    public async shuffle(mix: CubeAction[]) {
        for (let i = 0; i < mix.length; i++) {
            this._queue.push(mix[i]);
        }
        this._processQueue();
    } 

    public randomMix(): void {
        const movesArray = ["F", "D", "L", "R", "U", "B"];

        for (let i = 0; i < 30; i++) {
            const randomIndex = Math.floor(Math.random() * movesArray.length);
            let move = movesArray[randomIndex];
            const clockwise = Math.random() > 0.5;
            if (Math.random() < 0.3) move += "2";

            this._queue.push({ move, clockwise });
        }

        this._processQueue();
    }

    public reversemove(): void {
        if (this._mix.length < 1)
            return ;

        let reverse: CubeAction = {move: '', clockwise: true};

        const lastmove = this._mix[this._mix.length - 1];
        if (lastmove.move.includes("'")) {
            if (lastmove.move.includes('2')) {
                reverse.move = lastmove.move[0];
                reverse.clockwise = !lastmove.clockwise;
                this._mix[this._mix.length - 1].move = this._mix[this._mix.length - 1].move[0] + this._mix[this._mix.length - 1].move[2];
            } else {
                reverse.move = lastmove.move[0];
                reverse.clockwise = !lastmove.clockwise;
                this._mix.pop();
            }
        } else {
            if (lastmove.move.includes('2')) {
                reverse.move = lastmove.move[0] + "'";
                reverse.clockwise = !lastmove.clockwise;
                this._mix[this._mix.length - 1].move = this._mix[this._mix.length - 1].move[0];
            } else {
                reverse.move = lastmove.move + "'";
                reverse.clockwise = !lastmove.clockwise;
                this._mix.pop();
            }
        }
        this._queue.push(reverse);
        this._processQueue(false);
    }

    public reversecube(): void {
        const current = (this._cube.rotation.x % (2 * Math.PI) + 2 * Math.PI) % (2 * Math.PI);

        const target = current < 0.01 ? Math.PI : 0;

        gsap.to(this._cube.rotation, {
            x: target,
            duration: 0.5,
            overwrite: 'auto'
        });
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

    public execInput(input: string): void {
        const parse = input.split(' ');
        for (let i = 0; i < parse.length; i++) {
            const isClockwise = parse[i].includes("'");
            if (isClockwise && parse[i].length === 2) 
                parse[i] = parse[i][0];
            if (parse[i].includes("2")) {
                parse[i] = parse[i][0]
                this._queue.push({move: parse[i], clockwise: !isClockwise});
                this._queue.push({move: parse[i], clockwise: !isClockwise});
            } else
                this._queue.push({move: parse[i], clockwise: !isClockwise});
        }

        this._processQueue();
    }

    private async _processQueue(isPushToMix: boolean = true): Promise<void> {
        if (this._isAnimated || this._queue.length === 0)
            return;
        this._isAnimated = true;
        while (this._queue.length > 0) {
            const action = this._queue.shift()!;
            if (isPushToMix)
                this._pushToMix(action);
            await this._execAction(action);
            const adjustedSpeed = Math.max(0.001, this._speed - this._queue.length * 50);
            await this._sleep(adjustedSpeed);
        }

        this._isAnimated = false;
    }

    private async _sleep(ms: number): Promise<void> {
        return new Promise(
            resolve => setTimeout(resolve, ms)
        );
    }

    private _pushToMix(operation: CubeAction): void {
        if (!operation.clockwise && !operation.move.includes("'")) {
            operation.move += "'";
        }
        if (this._mix.length > 0
            && operation.move === this._mix[this._mix.length - 1].move 
            && operation.clockwise === this._mix[this._mix.length - 1].clockwise
        ) {
            if (operation.clockwise)
                this._mix[this._mix.length - 1].move += "2";
            else
                this._mix[this._mix.length - 1].move = operation.move[0] + "2'";
        } else {
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
        const background = document.getElementsByClassName("background");
        const moves = this._mix.map(action => action.move).join(" ");
        background[0].innerHTML = moves;
    }

    private async _execAction(action: CubeAction) {
        const count = action.move.includes("2") ? 2 : 1;
        const base = action.move[0];
        const isPrime = !action.move.includes("'");

        for (let i = 0; i < count; i++) {
            switch (base) {
                case "F": this._rotate("F", isPrime); break;
                case "B": this._rotate("B", isPrime); break;
                case "L": this._rotate("L", isPrime); break;
                case "R": this._rotate("R", isPrime); break;
                case "U": this._rotate("U", isPrime); break;
                case "D": this._rotate("D", isPrime); break;
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

    public getMix(): CubeAction[] { return this._mix; }

}