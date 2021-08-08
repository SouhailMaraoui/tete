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
    const [loading,setLoading]=useState(true);
    const [activeLink,setActiveLink]=useState(0);

    useEffect(()=>{
        workerObj.elems.then(workers=>{
            workerObj.elems=workers;
            setLoading(false);
        })
        scriptObj.elems.then(scripts=>{
            scriptObj.elems=scripts;
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
            <EuiPageTemplate paddingSize={"none"} restrictWidth={false} style={{paddingTop:59, height:"100vh"}}
                pageHeader={{
                    iconType: navLinks[activeLink].iconType,
                    pageTitle: navLinks[activeLink].label,
                }}>
                <EuiSpacer size={"l"}/>
                <EuiHorizontalRule margin={"none"} className={"mt-n4"}/>
                {loading
                    ? <div>Loading</div>
                    : [activeLink===0 && <Table obj={workerObj} type={"worker"}/>,
                        activeLink===1 && <Table obj={scriptObj} type={"script"} workerObj={workerObj}/>]
                }
            </EuiPageTemplate>
        </div>
    )
}