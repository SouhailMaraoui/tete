import React, {useState, useEffect} from 'react';

import {
    EuiBasicTable,
    EuiButton,
} from '@elastic/eui';

import {Modal} from "./Modal";
import {RunModal} from "./RunModal";

export const Table = ({obj,type,runnerObj,workerObj}) => {

    const [add, setAdd] = useState(false);
    const [runScript, setRunScript] = useState(null);
    const [sortField, setSortField] = useState('id');
    const [sortDirection, setSortDirection] = useState('asc');
    const [pageOfItems,setPageOfItems]=useState([])

    const sorting = {
        sort: {
            field: sortField,
            direction: sortDirection,
        },
    };

    const onTableChange = ({sort = {} }) => {
        const { field: sortField, direction: sortDirection } = sort;
        setSortField(sortField);
        setSortDirection(sortDirection);
    };

    const renderFooterName = () => {
        return (
            <EuiButton color="primary" iconType="plus" onClick={()=>setAdd(!add)} style={{maxHeight:30}}>
                Add new...
            </EuiButton>
        )
    }


    const actions = [
        {
            name: 'Delete',
            description: 'Delete',
            icon: 'trash',
            type: 'icon',
            color: 'danger',
            onClick: (e)=>{obj.remove(e.id)},
        }
    ];

    const getActions = () =>{
        let actions = [
            {
                name: 'Delete',
                description: 'Delete',
                icon: 'trash',
                type: 'icon',
                color: 'danger',
                onClick: (e)=>{obj.remove(e.id)},
            }
        ];
        if(type==="script") actions.push({
            name: 'Rune',
            description: 'Run',
            icon: 'push',
            type: 'icon',
            color: 'primary',
            onClick: (e)=>{setRunScript(e)},
        })
    }

    let columns = [
        {
            field: 'id',
            name: 'id',
            align: "center",
            sortable: true,
            truncateText: true,
            footer: renderFooterName,
        },
        {
            field: 'name',
            name: 'Name',
            align: "center",
            sortable: true,
            truncateText: true,
        },
        {
            field: 'field',
            name: type==="worker"?'Address':'Script',
            align: "center",
            sortable: true,
            truncateText: true,
        },
        {
            name: 'Actions',
            width:"100px",
            actions
        }
    ];

    useEffect(()=>{
        setPageOfItems(obj.elems.map(elm=>({
            id:elm.id,
            name:elm.name,
            field:elm.address || elm.script
        })));
    },[])

    return (
        <div>
            <EuiBasicTable
                className="table"
                items={pageOfItems}
                itemId="id"
                columns={columns}
                sorting={sorting}
                onChange={onTableChange}
            />
            {add && <Modal obj={obj} type={type} setAdd={setAdd}/>}
            {runScript && <RunModal setRun={setRunScript} runnerObj={runnerObj} script={runScript} workerObj={workerObj}/>}
        </div>
    );
};