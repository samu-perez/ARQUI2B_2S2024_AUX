const express = require("express");
const morgan = require("morgan");
const cors = require("cors");

// Importar el controlador Serial
require('./controllers/serialPortController');

const app = express();
const PORT = process.env.PORT || 3000;

// Middlewares
app.use(morgan("dev"));
app.use(cors());

// Route Initial API
app.get("/", (req, res) => {
    res.json({ message: "ARQUI2 - Fase 2 - API ARDUINO SERIAL" });
});
  
app.listen(PORT, () => {
    console.log(`API is listening on port ${PORT}`);
});