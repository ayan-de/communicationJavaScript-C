const { spawn } = require("node:child_process");
const fs = require("fs");

const numberFormatter = spawn("./number_formatter", ["./dest.txt", "$", ","]);
//if other application with node then we will use
//spawn("node", ["number_formatter.js","./dest.txt", "$", ","]);

numberFormatter.stdout.on("data", (data) => {
  console.log(`stdout: ${data}`);
});

numberFormatter.stderr.on("data", (data) => {
  console.log(`stderr: ${data}`);
});

numberFormatter.on("close", (code) => {
  if (code === 0) {
    console.log(`This file was read, processed and written successfully`);
  } else {
    console.log(`Something bad happened`);
  }
});

const fileStream = fs.createReadStream("./src.txt");
fileStream.pipe(numberFormatter.stdin);
