import React, {useEffect, useState} from 'react';

import 'brace/mode/yaml';

import {
    EuiButton,
    EuiButtonEmpty,
    EuiSelect,
    EuiForm,
    EuiFormRow,
    EuiModal,
    EuiModalBody,
    EuiModalFooter,
    EuiModalHeader,
    EuiModalHeaderTitle, EuiFlexGroup, EuiFlexItem, EuiLoadingSpinner, EuiIcon, EuiSpacer, EuiCode
} from '@elastic/eui';

export const RunModal = ({script,workers,runnerObj,setRun}) =>{

    const [isLoading,setIsLoading]=useState(false);
    const [response,setResponse]=useState({ExitCode:null,Message:null})
    const options=workers.map(elm=>({
        value:JSON.stringify(elm),
        text:elm.name
    }))
    const [worker,setWorker]=useState(options[0].value);

    const runScript = () =>{
        setIsLoading(true);
        runnerObj.run(worker,script).then(data=>{
            setResponse(data);
        })
    }

    const formSample = (
        <EuiForm id="modalFormId" component="form">

            <EuiFormRow label="Worker">
                <EuiSelect
                    disabled={isLoading}
                    id="workerSelect"
                    options={options}
                    value={worker}
                    onChange={(e) => setWorker(e.target.value)}
                />
            </EuiFormRow>

        </EuiForm>
    );

    const running = (
        <EuiFlexGroup justifyContent={"spaceAround"}>
            <EuiFlexItem>
                <div style={{textAlign:"center"}}>
                {response.ExitCode===null
                    ? <EuiLoadingSpinner size="xl"/>
                    : <div>
                        {response.ExitCode === '0' && <EuiIcon type={"checkInCircleFilled"} color={"success"} size={"xxl"}/>}
                        {response.ExitCode !== '0' && <EuiIcon type={"cross"} color={"danger"} size={"xxl"}/>}
                        {response.statusCode === 502 && <EuiIcon type={"alert"} color={"warning"} size={"xxl"}/>}
                        <EuiSpacer size={"xs"}/>
                        <br/>
                        {response.Message && <div>
                            <b>Last message :</b><EuiCode>{response.Message}</EuiCode>
                        </div>}
                        {response.reasonPhrase}
                    </div>
                }
                </div>
            </EuiFlexItem>
        </EuiFlexGroup>
    )

    return(
        <EuiModal onClose={()=>setRun(null)}>
            <EuiModalHeader>
                <EuiModalHeaderTitle>
                    <h1>Run script</h1>
                </EuiModalHeaderTitle>
            </EuiModalHeader>

            <EuiModalBody style={{height:100}}>
                {!isLoading
                    ? formSample
                    : running
                }
            </EuiModalBody>

            <EuiModalFooter>
                <EuiFlexGroup justifyContent={"spaceAround"}>
                    <EuiFlexItem>
                        <EuiButtonEmpty onClick={()=>setRun(null)}>Close</EuiButtonEmpty>
                    </EuiFlexItem>
                    {!isLoading && <EuiFlexItem>
                        <EuiButton form="RunModalFormId" onClick={runScript} fill>
                            Run
                        </EuiButton>
                    </EuiFlexItem>}
                </EuiFlexGroup>


            </EuiModalFooter>
        </EuiModal>
    )

}