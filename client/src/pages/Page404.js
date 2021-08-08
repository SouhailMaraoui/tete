import React, { Component} from 'react';
import {EuiEmptyPrompt, EuiPageTemplate} from "@elastic/eui";

class Page404 extends Component {
    render() {
        return (

            <EuiPageTemplate
                template="centeredBody"
                pageContentProps={{ paddingSize: 'none' }}>
                <EuiEmptyPrompt
                    title={<span>404</span>}
                    body={<span>The page you were looking for was not found.</span>}
                />
            </EuiPageTemplate>
        );
    }
}

export default Page404;