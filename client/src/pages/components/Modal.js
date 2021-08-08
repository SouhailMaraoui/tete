import React, {useEffect, useState} from 'react';

import 'brace/mode/yaml';

import {
    EuiButton,
    EuiButtonEmpty,
    EuiFieldText,
    EuiForm,
    EuiFormRow,
    EuiModal,
    EuiModalBody,
    EuiModalFooter,
    EuiModalHeader,
    EuiModalHeaderTitle,
    EuiCodeEditor,
} from '@elastic/eui';

export const Modal = ({obj,type,setAdd,setElems}) =>{


    const [isLoading,setLoading]=useState(false);

    const getNewElm = () =>{
        if(type==="worker")
            return {name:"",address:""}
        if(type==="script")
            return {name:"",script:""}
    }

    const [newElm,setNewElm]=useState(getNewElm())


    const addElm = () =>{
        setLoading(true);
        obj.add(newElm).then(()=>{
            obj.getAll().then(elms=> {
                setElems(elms)

                setLoading(false);
                setAdd(false);
                setNewElm(getNewElm());
            })
        })
    }

    const formSample = (
        <EuiForm id="modalFormId" component="form">

            <EuiFormRow label="Name">
                <EuiFieldText onChange={(e)=>setNewElm({...newElm,name:e.target.value})}/>
            </EuiFormRow>

            {type==="worker" &&
            <EuiFormRow label="Address">
                <EuiFieldText value={newElm.address} onChange={(e)=>setNewElm({...newElm,address:e.target.value})}/>
            </EuiFormRow>}

            {type==="script" &&
            <EuiFormRow label="Script">
                <EuiCodeEditor
                    mode="yaml" style={{height:"250px"}}
                    value={newElm.script} onChange={(e)=>setNewElm({...newElm,script:e})}/>
            </EuiFormRow>}
        </EuiForm>
    );

    return(
        <EuiModal onClose={()=>setAdd(false)} initialFocus="[name=popswitch]">
            <EuiModalHeader>
                <EuiModalHeaderTitle>
                    <h1>Add a new item</h1>
                </EuiModalHeaderTitle>
            </EuiModalHeader>

            <EuiModalBody>{formSample}</EuiModalBody>

            <EuiModalFooter>
                <EuiButtonEmpty onClick={()=>setAdd(false)}>Cancel</EuiButtonEmpty>

                <EuiButton form="modalFormId" onClick={addElm} fill isLoading={isLoading}>
                    Save
                </EuiButton>
            </EuiModalFooter>
        </EuiModal>
    )

}