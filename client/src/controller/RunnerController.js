import RunnerInterface from "../interface/RunnerInterface";

export class RunnerController{
    constructor() {
        this.interface=new RunnerInterface();
    }

    run(worker,script){
        return this.interface.run(worker,script);
    }
}