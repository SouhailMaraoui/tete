import React, {useState, useEffect} from 'react';

import {
    EuiBasicTable,
    EuiButton,
    EuiCodeBlock,
    EuiButtonEmpty
} from '@elastic/eui';

import {Modal} from "./Modal";
import {RunModal} from "./RunModal";

export const Table = ({obj,elems,setElems,type,runnerObj,workers}) => {

    const [isLoading,setLoading]=useState(-1);
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
                Add item
            </EuiButton>
        )
    }

    let actions = [
        {
            name: 'Delete',
            description: 'Delete',
            render:(elm)=> {
                const idx=pageOfItems.findIndex(e=>e.id===elm.id)
                return <EuiButtonEmpty isLoading={isLoading===idx} color={"danger"} display="base" onClick={()=>{removeElm(elm.id)}}
                                       iconType="trash" size="s" style={{maxWidth:"20px"}}/>
            }
        }
    ];

    if(actions.length===1 && type==="script" && workers.length>0) actions.push({
        name: 'Rune',
        description: 'Run',
        icon: 'push',
        type: 'icon',
        color: 'primary',
        onClick: (e)=>{setRunScript({id:e.id,script:e.field,name:e.name})},
    })

    const removeElm = (elmId) =>{
        const idx=pageOfItems.findIndex(e=>e.id===elmId)
        setLoading(idx);
        obj.remove(elmId).then(()=> {
                obj.getAll().then(elms => {
                    setElems(elms);
                    setLoading(-1);
                })
            }
        )
    }

    let columns = [
        {
            field: 'id',
            name: 'id',
            align: "center",
            sortable: true,
            width:"150px",
            truncateText: true,
            footer: renderFooterName,
        },
        {
            field: 'name',
            name: 'Name',
            align: "center",
            width:"300px",
            sortable: true,
            truncateText: true,
        },
        {
            field: 'field',
            name: type==="worker"?'Address':'Script',
            align: "center",
            sortable: false,
            render : (elm)=>{
                if(type==="worker") return elm;
                return <EuiCodeBlock style={{border:"1px solid black", borderRadius:5, textAlign:"left", width:400, padding:5}}
                                     fontsize={"s"} paddingSize={"none"} language="yaml">{elm}</EuiCodeBlock>
            }
        },
        {
            name: 'Actions',
            width:"150px",
            actions
        }
    ];

    useEffect(()=>{
        setPageOfItems(elems.map(elm=>({
            id:elm.id,
            name:elm.name,
            field:elm.address || elm.script
        })));
    },[elems])

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
            {add && <Modal obj={obj} type={type} setAdd={setAdd} elems={elems} setElems={setElems}/>}
            {runScript && <RunModal setRun={setRunScript} runnerObj={runnerObj} script={runScript} workers={workers}/>}
        </div>
    );
};