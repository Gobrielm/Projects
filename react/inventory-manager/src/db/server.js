import express from 'express';
import sql from 'mssql/msnodesqlv8.js'
import cors from 'cors';
import bcrypt from 'bcrypt';

const app = express();

app.use(cors({
  origin: 'http://localhost:5173'  // or '*' to allow all
}));

app.use(express.json()); // allows JSON body parsing


const config = {
  server: 'GabePC\\SQLSERVER',
  database: 'TESTDB',
  driver: 'msnodesqlv8',
  options: {
    trustedConnection: true
  }

  /* Users
      userId (unique) 
      username
      passwordEnc
      salt
  */
};



async function testConnection() {
  try {
    let pool = await sql.connect(config);

    // test fetching one user with ID = 1
    const result = await pool
      .request()
      .input('userId', sql.Int, 1)
      .query('SELECT * FROM Users WHERE UserId = @userId');

    console.log('Test query result:', result.recordset);
  } catch (err) {
    console.error('SQL error:', JSON.stringify(err, Object.getOwnPropertyNames(err), 2));
  }
}

testConnection();

app.get('/Users', async (req, res) => {
  try {
    const { userId } = req.query;
    
    let pool = await sql.connect(config);

    const data = await pool
      .request()
      .input('userId', sql.Int, userId)
      .query('SELECT * FROM Users WHERE userId = @userId');
    
    res.json(data.recordset);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Server error" });
  }
});

app.post('/Users', async (req, res) => {
  const { userId, username, passwordEnc, salt } = req.body;
  let pool = await sql.connect();

  const saved = await pool.request()
    .input('userId', sql.Int, userId)
    .input('username', sql.VarChar(30), username)
    .input('passwordEnc', sql.VarChar(50), passwordEnc)
    .input('salt', sql.VarChar(30), salt)
    .query('INSERT INTO Users VALUES(@userId, @username, @passwordEnc, @salt)')

  res.json(saved);
});

app.delete('/Users', async (req, res) => {
  const { userId, username, passwordEnc, salt } = req.body;
  let pool = await sql.connect();

  const data = await pool
      .request()
      .input('userId', sql.Int, userId)
      .query('SELECT * FROM Users WHERE userId = @userId');
    let jsoned = json(data);
    
    if (jsoned.username !== username || jsoned.passwordEnc !== passwordEnc || jsoned.salt !== salt) {
      res.status(400).json({error: "Wrong username or password"});
    } else {
      const saved = await pool.request()
        .input('userId', sql.Int, userId)
        .query('DELETE FROM Users WHERE userId = @userId')
      res.json(saved);
    }
    
})

// Start Express server
app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});