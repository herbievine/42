import { customAlphabet } from "nanoid";

const alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const length = 12;

const nanoid = customAlphabet(alphabet, length);

export function id() {
  return nanoid();
}
