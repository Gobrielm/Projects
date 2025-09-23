import sql from 'mssql/msnodesqlv8.js'

const config = {
  server: 'GabePC\\SQLSERVER',
  database: 'TestDB',
  driver: 'msnodesqlv8',
  options: {
    trustedConnection: true
  }
};

async function testConnection() {
  try {
    let pool = await sql.connect(config);
    const result = await pool.request()
      .input('name', sql.NVarChar, 'Alice')
      .input('email', sql.NVarChar, 'alice@example.com')
    .query('INSERT INTO Users (name, email) VALUES (@name, @email)');



    
    console.log(result.recordset);
  } catch (err) {
    console.error('SQL error', err);
  }
}

testConnection();
