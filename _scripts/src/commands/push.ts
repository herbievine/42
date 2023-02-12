import z from "zod";
import fs from "fs-extra";
import { exec } from "child_process";
import path from "path";
import parseError from "../lib/parseError";
import run from "../lib/run";

const PushCommand = z.tuple([
  z.string(),
  z
    .string()
    .regex(
      /^(https:\/\/[\w\d]+\.\w+\/|git@[\w\d]+\.\w+:)([\w\d]+\/)*([\w\d]+\.git)$/
    ),
  z.object({
    clean: z.string().optional(),
  }),
  z.any(),
]);

const push = async (...props: any[]) => {
  const [dir, url, opts] = PushCommand.parse(props);
  const tmpFolder = process.env.HOME + "/tmp/42-cli";
  const whitelistedFiles: string[] = [];

  try {
    console.log(`Cloning your project...`);

    if (!(await fs.exists(tmpFolder))) {
      await fs.mkdir(tmpFolder, { recursive: true });
    }

    await fs.copy(dir, tmpFolder, {
      filter: (src) => {
        if (fs.existsSync(src) && fs.lstatSync(src).isDirectory()) {
          return true;
        }

        const regex = new RegExp(opts.clean || "");

        if (regex.test(src)) return true;

        return false;
      },
    });
  } catch (error) {
    parseError(
      "Could not copy your project to the temporary folder. Make sure the path is correct and that you have the right permissions.",
      error
    );
  }

  console.log(whitelistedFiles);

  try {
    console.log(`Initializing your git repo...`);

    const commands = [
      `git init`,
      `git add .`,
      `git commit -m "first commit"`,
      `git branch -M main`,
      `git remote add origin ${url}`,
      `git push -u origin main`,
    ];

    for (const command of commands) {
      console.log(`Running: ${command}`);
      const details = await run(`cd ${tmpFolder} && ${command}`);
      console.log(details);
    }
  } catch (error) {
    parseError(
      "An error occured while trying to push your project. Make sure you have the right permissions and that the git url is correct.",
      error
    );
  }

  try {
    console.log(`Cleaning up...`);

    await fs.remove(tmpFolder);
  } catch (error) {
    parseError(
      "Could not remove the temporary folder. Make sure you have the right permissions.",
      error
    );
  }

  console.log(`Pushed your project to ${url}`);
};

export default push;
