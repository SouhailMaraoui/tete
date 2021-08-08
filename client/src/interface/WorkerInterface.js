import axios from "axios";
import RESTProps from "../properties/RESTProps";

export default class WorkerInterface {

    getAll(){
        return axios.get(RESTProps.URL + RESTProps.WORKERS).then(response=>{
            return response.data;
        })
    }

    add(worker){
        return axios.post(RESTProps.URL + RESTProps.WORKERS,worker).then(response=>{
            return response.data;
        })
    }

    remove(workerId){
        return axios.delete(RESTProps.URL+ RESTProps.WORKERS+workerId).then(response=>{
            return response.data;
        })
    }
}