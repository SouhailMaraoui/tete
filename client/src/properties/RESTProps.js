
const RESTProps = {
    URL :process.env.DEPLOYUS_ADDR || "http://68.183.192.81:5001",
    WORKERS: "/api/workers/",
    SCRIPTS: "/api/scripts/",
    EXEC: "/exec/"
}


export default RESTProps;