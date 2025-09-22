import sql from 'mssql'

const config = {
  user: "gabri",
  password: "",
  server: "GABEPC\\SQLSERVER",         // or "127.0.0.1"
  database: "TestDB",
  options: {
    encrypt: false,            // set true if using Azure
    trustServerCertificate: true // required for local dev
  }
};

async function testConnection() {
  try {
    let pool = await sql.connect(config);
    let result = await pool.request().query("SELECT * FROM Users");
    console.log(result.recordset);
  } catch (err) {
    console.error("SQL error", err);
  }
}

testConnection();
