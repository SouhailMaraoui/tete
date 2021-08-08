import WorkerInterface from "../interface/WorkerInterface";

export class WorkerController{
    constructor() {
        this.interface=new WorkerInterface();
        this.elems=this.interface.getAll();
    }

    add(worker){
        return this.interface.add(worker);
    }
    remove(workerId){
        return this.interface.remove(workerId);
    }
}