import React, {useEffect, useState} from "react";
import { EuiCollapsibleNavGroup, EuiCollapsibleNav, EuiHorizontalRule, EuiSpacer, EuiPinnableListGroup, EuiPageTemplate } from '@elastic/eui';

import {Table} from "./components/Table";

import {WorkerController} from "../controller/WorkerController";
import {ScriptController} from "../controller/ScriptController";
import {RunnerController} from "../controller/RunnerController";

//Static Objects
const workerObj=new WorkerController();
const scriptObj=new ScriptController();
const runnerObj=new RunnerController();

export default function Dashboard() {
    const [workers,setWorkers] = useState(null)
    const [scripts,setScripts] = useState(null)
    const [activeLink,setActiveLink]=useState(0);

    useEffect(()=>{
        workerObj.getAll().then(workers=>{
            setWorkers(workers);
        })
        scriptObj.getAll().then(scripts=>{
            setScripts(scripts)
        })
    },[])

    const WorkerLink={
        label: 'Workers',
        iconType: 'user',
        isActive: activeLink===0,
        onClick:()=>setActiveLink(0),
        pinnable: false,
    }
    const ScriptLink={
        label: 'Scripts',
        iconType: 'apmTrace',
        isActive: activeLink===1,
        onClick:()=>setActiveLink(1),
        pinnable: false,
    }

    const navLinks= [WorkerLink,ScriptLink];

    const sideNav=(
        <EuiCollapsibleNav
            id="guideCollapsibleNavAllExampleNav"
            isOpen={true}
            isDocked={true}
            onClose={()=>{}}
            size={225}>
            <EuiCollapsibleNavGroup
                background={"light"}
                title="DeployUs"
                iconType="usersRolesApp"
                isCollapsible={true}
                initialIsOpen={true}>
                <EuiPinnableListGroup
                    listItems={navLinks}
                    onPinClick={() => {}}
                    maxWidth="none"
                    color="subdued"
                    gutterSize="none"
                    size="m"
                />
            </EuiCollapsibleNavGroup>
        </EuiCollapsibleNav>
    );

    return (
        <div>
            {sideNav}
            <EuiPageTemplate paddingSize={"none"} restrictWidth={false} style={{paddingTop:5, height:"100vh"}}
                pageHeader={{
                    iconType: navLinks[activeLink].iconType,
                    pageTitle: navLinks[activeLink].label,
                }}>
                <EuiSpacer size={"l"}/>
                <EuiHorizontalRule margin={"none"} className={"mt-n4"}/>
                {activeLink===0 && (workers
                    ? <Table obj={workerObj} elems={workers} setElems={setWorkers} type={"worker"}/>
                    : <h3>Loading....</h3>)}
                {activeLink===1 && (scripts
                    ? <Table obj={scriptObj} elems={scripts} setElems={setScripts} type={"script"} workers={workers}/>
                    : <h3>Loading....</h3>)}
            </EuiPageTemplate>
        </div>
    )
}