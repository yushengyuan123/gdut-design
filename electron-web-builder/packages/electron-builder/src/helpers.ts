export function isArgFormatInvalid(arg: string): boolean {
  return (
    (arg.startsWith('---') ||
      /^--[a-z]$/i.exec(arg) !== null ||
      /^-[a-z]{2,}$/i.exec(arg) !== null) &&
    !['--x', '--y'].includes(arg) // exception for long args --{x,y}
  );
}