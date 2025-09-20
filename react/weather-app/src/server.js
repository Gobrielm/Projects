import express from 'express';
import mongoose from 'mongoose';
import cors from 'cors';

const app = express();

// Enable CORS for all origins (or restrict to your frontend URL)
app.use(cors({
  origin: 'http://localhost:5173'  // or '*' to allow all
}));

app.use(express.json()); // allows JSON body parsing

const password = 'Ioz1zWH1V31NSP2m'
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

// 2. Define a schema
const weatherSchema = new mongoose.Schema({
  city: { type: String, unique: true },
  temperature: Number,
  description: String,
  date: Date
});

// 3. Make a model
const Weather = mongoose.model('Weather', weatherSchema);

// 4. Add a GET route to fetch weather data from DB
app.get('/weather', async (req, res) => {
  const data = await Weather.find(); // fetch all documents
  res.json(data);
});

// 5. Add a POST route to save new weather data
app.post('/weather', async (req, res) => {
  const { city, temperature, description, date } = req.body;
  const saved = await Weather.findOneAndUpdate(
    { city },
    { temperature, description, date },
    { new: true, upsert: true }
  );
  res.json(saved);
});

// Start Express server
app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});
