import ScriptInterface from "../interface/ScriptInterface";

export class ScriptController{
    constructor() {
        this.interface=new ScriptInterface();
        this.elems=this.interface.getAll();
    }

    add(script){
        return this.interface.add(script);
    }
    remove(scriptId){
        return this.interface.remove(scriptId);
    }
}