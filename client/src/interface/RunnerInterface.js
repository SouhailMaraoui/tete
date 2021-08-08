import axios from "axios";
import RESTProps from "../properties/RESTProps";

export default class RunnerInterface {

    run(worker,script){
        const content={
            worker:worker,
            script:script
        }
        return axios.post(RESTProps.URL + "/role/create",content).then(response=>{
            return response.data;
        })
    }
}