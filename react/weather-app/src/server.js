import express from 'express';
import mongoose from 'mongoose';
import cors from 'cors';

const app = express();

const { API_KEY } = import("./api_keys/config.cjs");
const password = encodeURIComponent(import("./api_keys/config.cjs"))
const BASE_URL = 'https://api.openweathermap.org/data/2.5/';

app.use(cors({
  origin: 'http://localhost:5173'
}));

app.use(express.json());

const uri = `mongodb+srv://gobrielmc:${password}@cluster0.ojghum0.mongodb.net/?appName=Cluster0`;

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


const weatherSchema = new mongoose.Schema({
  city: { type: String, unique: true },
  temperature: Number,
  description: String,
  date: Date
});


const Weather = mongoose.model('Weather', weatherSchema);


app.get('/weather', async (req, res) => {
  const data = await Weather.find(); // fetch all documents

  if (data == null) {
    data = await fetch(
      `${BASE_URL}weather?q=${city}&appid=${API_KEY}&units=metric`
    );
  }


  res.json(data);
});


app.post('/weather', async (req, res) => {
  const { city, temperature, description, date } = req.body;
  const saved = await Weather.findOneAndUpdate(
    { city },
    { temperature, description, date },
    { new: true, upsert: true }
  );
  res.json(saved);
});


app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});
