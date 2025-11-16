import { useState } from 'react'
import './styles.css';

function UnitSelector({onChangeUnits}) {
  const [isCelsuis, setValue] = useState(true);

  const handleChange = (event) => {
    const newValue = !isCelsuis;
    setValue(newValue);
    onChangeUnits(newValue);
  }

  return (
    <>
      <label className="TempSwitch">
        Fahrenheit
        <input type="checkbox"
        onChange={handleChange}
        />
      </label>
    </>
  )
}


function CityTextbox({onCitySubmit}) {
  const [text, setText] = useState('');

  const handleChange = (event) => {
    setText(event.target.value);
  };

  const handleKeyDown = (event) => {
    if (event.key === "Enter") {
      onCitySubmit(text); // send city up
      setText(""); // clear input
    }
  };

  return (
    <div>
      <label htmlFor="myInput">Enter City Here:</label>
      <input
        type="text"
        id="cityInput"
        value={text}
        onChange={handleChange}
        placeholder="City Here..."
        onKeyDown={handleKeyDown}
      />
    </div>
  );
}

const DATATIMEOUT = 3600000;

function App() {
  const [weatherData, setWeatherData] = useState(null);
  const [isCelsuis, setValue] = useState(true);

  const getWeatherData = async (city) => {
    // Replace with your real API key + endpoint
    let res = await fetch("http://localhost:3000/weather");
    let saved = await res.json();
    let existing = saved.find((w) => w.city.toLowerCase() === city.toLowerCase());
    const dateA = new Date();
    const dateB = new Date(existing.date);

    const is_data_valid = (dateB != undefined && (dateB.getTime() - dateA.getTime()) < DATATIMEOUT);


    if (existing && is_data_valid) {
      setWeatherData(existing);
    } else {
      console.log("Fetched from API to give to database");
      res = await fetch(
        `${BASE_URL}weather?q=${city}&appid=${API_KEY}&units=metric`
      );
      const data = await res.json();

      if (data.cod !== 200) {
        console.error("City not found:", data.message);
        return;
      }

      saveWeatherToDB(data);

      setWeatherData({
        city: data.name,
        temperature: data.main.temp,
        description: data.weather[0].description,
      });
    }
  };

  return (
    <div className = "WeatherHomePage">
      <CityTextbox onCitySubmit={getWeatherData} />
      <UnitSelector onChangeUnits={setValue}/>
      <table id="WeatherDataMenu">
        <tbody>
          <DisplayWeather data={weatherData} isCelsuis={isCelsuis}/>
        </tbody>
      </table>
    </div>
  );
}

function saveWeatherToDB(weatherData) {
  fetch("http://localhost:3000/weather", {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({
      city: weatherData.name,
      temperature: weatherData.main.temp,
      description: weatherData.weather[0].description,
      date: new Date()
    })
  })
    .then(res => res.json())
    .then(savedData => {
      console.log("Saved to DB:", savedData);
    })
    .catch(err => console.error("Error saving weather:", err));
}

function celsiusToFahrenheit(celsius) {
  return (celsius * 9/5) + 32;
}

function DisplayWeather({data, isCelsuis}) {
  if (!data) {
    return null; // nothing until data exists
  }

  let temp = isCelsuis ? data.temperature: celsiusToFahrenheit(data.temperature);
  temp = temp.toFixed(1);
  temp += isCelsuis ? "°C": "°F";

  return (
    <tr>
      <td>{data.city}</td>
      <td>{temp}</td>
      <td>{data.description}</td>
    </tr>
  );
}

export default App
