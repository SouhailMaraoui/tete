import axios from "axios";
import RESTProps from "../properties/RESTProps";

export default class ScriptInterface {

    getAll(){
        return axios.get(RESTProps.URL + RESTProps.SCRIPTS).then(response=>{
            return response.data
        })
    }

    add(script){
        return axios.post(RESTProps.URL + RESTProps.SCRIPTS, script).then(response=>{
            return response.data;
        })
    }

    remove(scriptId){
        return axios.delete(RESTProps.URL+ RESTProps.SCRIPTS+scriptId).then(response=>{
            return response.data;
        })
    }
}