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
    EuiModalHeaderTitle
} from '@elastic/eui';

export const RunModal = ({script,workers,runnerObj,setRun}) =>{

    const options=workers.map(elm=>({
        value:JSON.stringify(elm),
        text:elm.name
    }))
    const [worker,setWorker]=useState(options[0].value);

    const runScript = () =>{
        runnerObj.run(worker,script);
    }

    const formSample = (
        <EuiForm id="modalFormId" component="form">

            <EuiFormRow label="Worker">
                <EuiSelect
                    id="workerSelect"
                    options={options}
                    value={worker}
                    onChange={(e) => setWorker(e.target.value)}
                />
            </EuiFormRow>

        </EuiForm>
    );

    return(
        <EuiModal onClose={()=>setRun(null)} initialFocus="[name=popswitch]">
            <EuiModalHeader>
                <EuiModalHeaderTitle>
                    <h1>Run script</h1>
                </EuiModalHeaderTitle>
            </EuiModalHeader>

            <EuiModalBody>{formSample}</EuiModalBody>

            <EuiModalFooter>
                <EuiButtonEmpty onClick={()=>setRun(null)}>Cancel</EuiButtonEmpty>

                <EuiButton form="RunModalFormId" onClick={runScript} fill>
                    Run
                </EuiButton>
            </EuiModalFooter>
        </EuiModal>
    )

}