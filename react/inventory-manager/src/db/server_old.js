import express from 'express';
import mongoose, { mongo } from 'mongoose';
import cors from 'cors';
import dotenv from "dotenv";
dotenv.config();

const app = express();

// Enable CORS for all origins (or restrict to your frontend URL)
app.use(cors({
  origin: 'http://localhost:5173'  // or '*' to allow all
}));

app.use(express.json()); // allows JSON body parsing

const password = process.env.MONGO_DB_PASS;

const uri = `mongodb+srv://gobrielmc:${password}@cluster0.ojghum0.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0`;

async function run() {
  try {
    await mongoose.connect(uri, {});

    // Check connection by pinging admin database
    const admin = mongoose.connection.db.admin();
    await admin.command({ ping: 1 });
    console.log("Pinged your deployment. You successfully connected to MongoDB!");
  } catch (err) {
    console.error("Connection error:", err);
  }
}

run();

const userSchema = new mongoose.Schema({
  user: { id: int, unique: true },
  password: Number
});

const ObjectSchema = new mongoose.Schema({
  name: { type: String, unique: true },
  amount: Number
});

const DayStockSchema = new mongoose.Schema({
  date: { type: Date, unique: true },
  objects: [ObjectSchema],
  userId: Number
});

// Used for the daily stock tallying
const DayStock = mongoose.model('day_stock', DayStockSchema);

// For users
const users = mongoose.model('users', userSchema);


app.get('/day_stock', async (req, res) => {
  try {
    const { date } = req.query;
    const data = await DayStock.find({ date: new Date(date) });
    res.json(data);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Server error" });
  }
});


app.post('/day_stock', async (req, res) => {
  const { date, objects } = req.body;
  const saved = await Weather.findOneAndUpdate(
    { city },
    { temperature, description, date },
    { new: true, upsert: true }
  );
  res.json(saved);
});

app.delete('/day_stock', async (req, res) => {

})

// Start Express server
app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});
