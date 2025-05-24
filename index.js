// index.js
const abe = require('./build/Release/abe');

const policy = "A,B";
const plaintext = "Secret message";
const ciphertext = abe.encrypt(policy, plaintext);
console.log("Encrypted:", ciphertext);

const attributes = "A,B,C";
const decrypted = abe.decrypt(attributes, ciphertext);
console.log("Decrypted:", decrypted);
