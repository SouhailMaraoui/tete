import axios from "axios";
import RESTProps from "../properties/RESTProps";

export default class RunnerInterface {

    run(worker,script){
        const content={
            worker:JSON.parse(worker),
            script:script
        }
        return axios.post(RESTProps.URL + RESTProps.EXEC,content).then(response=>{
            return response.data;
        })
    }
}